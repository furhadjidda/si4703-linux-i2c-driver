/*
 * si4703.c
 *
 *  Created on: Jan 2, 2017
 *      Author: furhad
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/init.h>
//for platform drivers....
#include <linux/platform_device.h>

#include "si4703_include.h"

MODULE_LICENSE("GPL");
static int major;

static int si4703_probe(struct platform_device *pdev)
{
	printk(KERN_ALERT "\n Welcome to Si4703 Driver \n");
 	return 0;
}

static int si4703_remove(struct platform_device *pdev)
{
	return 0;
}


static struct of_device_id my_dev_id[] = {
	{
		.compatible = DRIVER_NAME
	},
	{}
};

MODULE_DEVICE_TABLE(of,my_dev_id);

static struct platform_driver si4703_driver = {
	.probe          = si4703_probe,
	.remove         = si4703_remove,
	.driver = {
			.name  = DRIVER_NAME,
			.of_match_table = my_dev_id,
	},
};


static long si4703_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return -EINVAL;
}

static int si4703_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "\n si4703_open called \n");
	return 0;
}

static int  si4703_close(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "\n si4703_close called \n");
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
	printk(KERN_ALERT "\n Welcome to si4703 Platform driver.... \n");

	major = register_chrdev(MAJOR_DYNAMIC, DRIVER_NAME, &sample_fops);
	/* major = register_chrdev(MAJOR_HARDCODE, DRV_NAME, &sample_fops);*/
	if (major < 0)
	{
		printk(KERN_ERR "%s: couldn't get a major number.\n", DRIVER_NAME);

		return major;
	}
	platform_driver_register(&si4703_driver);
	return 0;
}

void si4703_cleanup(void)
{
	platform_driver_unregister(&si4703_driver);
	unregister_chrdev(major, DRIVER_NAME);

	printk(KERN_ALERT "\n Exiting Si4703 Platform driver... \n");

	return;
}


module_init(si4703_init);
module_exit(si4703_cleanup);



