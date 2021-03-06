/*
 * Copyright (c) 2016-2017 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __PERIPHERAL_INTERFACE_I2C_H__
#define __PERIPHERAL_INTERFACE_I2C_H__

#include "peripheral_interface_common.h"

#define I2C_BUFFER_MAX 64

#define I2C_SLAVE	0x0703	/* Use this slave address */
#define I2C_SMBUS	0x0720	/* SMBus transfer */

/* i2c_smbus_xfer read or write markers */
#define I2C_SMBUS_READ	1
#define I2C_SMBUS_WRITE	0

/* SMBus transaction types */
#define I2C_SMBUS_QUICK		    0
#define I2C_SMBUS_BYTE		    1
#define I2C_SMBUS_BYTE_DATA	    2
#define I2C_SMBUS_WORD_DATA	    3

/*
 * Data for SMBus Messages
 */
#define I2C_SMBUS_BLOCK_MAX	32	/* As specified in SMBus standard */

union i2c_smbus_data {
	uint8_t byte;
	uint16_t word;
	uint8_t block[I2C_SMBUS_BLOCK_MAX + 2]; /* block[0] is used for length */
			       /* and one more for user-space compatibility */
};

/* This is the structure as used in the I2C_SMBUS ioctl call */
struct i2c_smbus_ioctl_data {
	uint8_t read_write;
	uint8_t command;
	uint32_t size;
	union i2c_smbus_data *data;
};

void peripheral_interface_i2c_close(peripheral_i2c_h i2c);
int peripheral_interface_i2c_read(peripheral_i2c_h i2c, uint8_t *data, uint32_t length);
int peripheral_interface_i2c_write(peripheral_i2c_h i2c, uint8_t *data, uint32_t length);
int peripheral_interface_i2c_read_register_byte(peripheral_i2c_h i2c, uint8_t reg, uint8_t *data_out);
int peripheral_interface_i2c_write_register_byte(peripheral_i2c_h i2c, uint8_t reg, uint8_t data_in);
int peripheral_interface_i2c_read_register_word(peripheral_i2c_h i2c, uint8_t reg, uint16_t *data_out);
int peripheral_interface_i2c_write_register_word(peripheral_i2c_h i2c, uint8_t reg, uint16_t data_in);

#endif /* __PERIPHERAL_INTERFACE_I2C_H__ */
