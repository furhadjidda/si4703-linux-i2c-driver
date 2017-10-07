/*
 * drivers/media/radio/si4703/si4703_include.h
 *
 * I2C client driver header for Si4703
 *
 * Copyright (c) 2017 Furhad Jidda
 * Author: Furhad Jidda<furhadjidda@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef CODE_SI4703_INCLUDE_H_
#define CODE_SI4703_INCLUDE_H_


#define DRIVER_NAME	"si4703_driver"

#define MAJOR_DYNAMIC 	0
#define MAJOR_HARDCODE 	189
#define BUFFER_LENGTH 	2048
#define DEVICE_NAME 	"i2cchar"    ///< The device will appear at /dev/ebbchar using this value
#define CLASS_NAME  	"i2c"        ///< The device class -- this is a character device driver

struct si4703_dev {
	struct mutex mutex;
	struct cdev cdev;
};

#endif /* CODE_SI4703_INCLUDE_H_ */
