/*
 * drivers/media/radio/si4703/protocol_struct.h
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
#ifndef CODE_PROTOCOL_STRUCT_H_
#define CODE_PROTOCOL_STRUCT_H_

enum Command{
	TUNE=0x12,
	SEEK_UP,
	SEEK_DOWN,
	TUNE_DIR_UP,
	TUNE_DIR_DOWN,
};

struct Message{
	enum Command Id;
	unsigned int freq;
};



#endif /* CODE_PROTOCOL_STRUCT_H_ */
