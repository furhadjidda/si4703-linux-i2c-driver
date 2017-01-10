/*
 * si4703.c
 *
 *  Created on: Jan 2, 2017
 *      Author: furhad
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include "si4703_include.h"

static int major;
static char kernelBuffer[BUFFER_LENGTH];
static struct class*  i2ccharClass  = NULL; ///< The device-driver class struct pointer
static struct device* i2ccharDevice = NULL; ///< The device-driver device struct pointer


struct i2cState {
	struct i2c_client*		i2cClient;
	struct i2c_device_id* 	i2cDeviceId;
};
struct i2cState *state;

static int si4703_probe(struct i2c_client *client,
						const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;

	if (!i2c_check_functionality(client->adapter, \
						I2C_FUNC_I2C))
	{
			dev_err(&client->dev, \
				"Need I2C_FUNC_I2C functions \n");
			printk(KERN_ERR "\n si4703_probe called error\n");
			return -ENODEV;
	}

	state = kzalloc(sizeof(struct i2cState), GFP_KERNEL);
	if (state == NULL)
	{
		dev_err(dev, "failed to create our state\n");
		return -ENOMEM;
	}
	state->i2cClient = client;
	i2c_set_clientdata(client, state);

	// initializing i2c
	gpio_free(23);
	gpio_free(0);

	gpio_request(23,"23");
	gpio_request(0,"0");
	gpio_direction_output(0,0);
	mdelay(500);
	gpio_direction_output(23,0);
	mdelay(500);
	gpio_direction_output(23,1);
	mdelay(500);

	printk(KERN_INFO "\n si4703_probe called \n");
	printk(KERN_INFO "\n Chip address=%d \n",client->addr);
 	return 0;
}

static int si4703_remove(struct i2c_client *client)
{
	struct i2cState *state = i2c_get_clientdata(client);

	kfree(state);

	return 0;
}


static const struct i2c_device_id si4703_dev_id[] = {
 { DRIVER_NAME, 0 },
 { }
};

MODULE_DEVICE_TABLE(i2c,si4703_dev_id);


static struct i2c_driver si4703_driver = {
	.probe = si4703_probe,
	.remove = si4703_remove,
	.id_table = si4703_dev_id,
	.driver = {
	.owner = THIS_MODULE,
	.name = DRIVER_NAME
	},
};

static long si4703_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return -EINVAL;
}

static int si4703_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "\n si4703_open called \n");
	return 0;
}

static int  si4703_close(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "\n si4703_close called \n");
	return 0;
}

ssize_t  si4703_read(struct file* file, char __user* buff, size_t len, loff_t * offset)
{
	printk(KERN_INFO "\n si4703_read called \n");
	return 0;
}



ssize_t  si4703_write(struct file* file,
					  const char __user* buffer,
					  size_t length,
					  loff_t* offset)
{
	ssize_t ret = 0;
	int bytes = 0;

	printk(KERN_INFO "\n si4703_write called \n");
	if( length >= BUFFER_LENGTH )
	{
		length = BUFFER_LENGTH;
	}

	ret = copy_from_user(kernelBuffer, buffer, length);

	printk(KERN_INFO "\n data to write %s \n",kernelBuffer);
	printk(KERN_INFO "\n Slave Address address = %d \n",state->i2cClient->addr);

	// Writing data in I2C Bus
	bytes = i2c_master_send(state->i2cClient, kernelBuffer, length);
	printk(KERN_INFO "\n # bytes written %d \n",bytes);

	return ret;
}

static const struct file_operations sample_fops = {
        .owner = THIS_MODULE,
        .unlocked_ioctl = si4703_ioctl,
        .open           = si4703_open,
        .release        = si4703_close,
		.read 			= si4703_read,
		.write 			= si4703_write

};

int si4703_init(void)
{
	int res = 0;
	printk(KERN_INFO "\n si4703_init called, Welcome to si4703 driver!! \n");

	major = register_chrdev(MAJOR_DYNAMIC, DRIVER_NAME, &sample_fops);
	if (major < 0)
	{
		printk(KERN_ERR "%s: couldn't get a major number.\n", DRIVER_NAME);

		return major;
	}

   // Register the device class
   i2ccharClass = class_create( THIS_MODULE, CLASS_NAME );
   if ( IS_ERR( i2ccharClass ) )
   {
	  // Check for error and clean up if there is
	  unregister_chrdev( major, DEVICE_NAME );
	  printk(KERN_ALERT "Failed to register device class\n");
	  return PTR_ERR( i2ccharClass );// Correct way to return an error on a pointer
   }
   printk(KERN_INFO "device class registered correctly\n");

   if ((res = i2c_add_driver(&si4703_driver)))
   {
		printk("si4703-i2c_add_driver: Driver registration failed, module not inserted.\n");
		return res;
   }
   // Register the device driver
   i2ccharDevice = device_create(i2ccharClass,
		   	   	   	   	   	   	 NULL,
								 MKDEV(major, 0),
								 NULL,
								 DEVICE_NAME);

   if( IS_ERR( i2ccharDevice ) ) // Clean up if there is an error
   {
	  class_destroy(i2ccharClass);
	  unregister_chrdev(major, DEVICE_NAME);
	  printk(KERN_ALERT "Failed to create the device\n");
	  return PTR_ERR(i2ccharDevice);
   }

   // Made it! device was initialized
   printk(KERN_INFO "device class %s created correctly\n",CLASS_NAME);

   return 0;
}

void si4703_cleanup(void)
{
	device_destroy(i2ccharClass, MKDEV(major, 0)); // remove the device
	class_unregister(i2ccharClass); // unregister the device class
	class_destroy(i2ccharClass); // remove the device class
	i2c_del_driver(&si4703_driver);
	unregister_chrdev(major, DRIVER_NAME);

	printk(KERN_INFO "\n Exiting Si4703 driver... \n");

	return;
}


module_init(si4703_init);
module_exit(si4703_cleanup);

MODULE_DESCRIPTION("SI4703 I2C client driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Furhad Jidda");

