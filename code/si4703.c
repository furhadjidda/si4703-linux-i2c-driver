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
//for platform drivers....

#include "si4703_include.h"

static int major;

static int si4703_probe(struct i2c_client *client,
						const struct i2c_device_id *id)
{
	printk(KERN_INFO "\n si4703_probe called \n");
	printk(KERN_INFO "\n Chip address=%d \n",client->addr);
 	return 0;
}

static int si4703_remove(struct i2c_client *client)
{
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

static const struct file_operations sample_fops = {
        .owner = THIS_MODULE,
        .unlocked_ioctl = si4703_ioctl,
        .open           = si4703_open,
        .release        = si4703_close
};

int si4703_init(void)
{
	printk(KERN_INFO "\n si4703_init called, Welcome to si4703 Platform driver!! \n");

	major = register_chrdev(MAJOR_DYNAMIC, DRIVER_NAME, &sample_fops);
	if (major < 0)
	{
		printk(KERN_ERR "%s: couldn't get a major number.\n", DRIVER_NAME);

		return major;
	}

	return i2c_add_driver(&si4703_driver);;
}

void si4703_cleanup(void)
{
	i2c_del_driver(&si4703_driver);
	unregister_chrdev(major, DRIVER_NAME);

	printk(KERN_INFO "\n Exiting Si4703 Platform driver... \n");

	return;
}


module_init(si4703_init);
module_exit(si4703_cleanup);

MODULE_DESCRIPTION("SI4703 I2C client driver");
MODULE_LICENSE("GPL");

