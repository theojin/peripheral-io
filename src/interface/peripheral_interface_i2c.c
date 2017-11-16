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

#include <sys/ioctl.h>

#include "peripheral_interface_i2c.h"

#define MAX_ERR_LEN 255

int peripheral_interface_i2c_close(peripheral_i2c_h i2c)
{
	int status = close(i2c->fd);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_i2c_read(peripheral_i2c_h i2c, uint8_t *data, uint32_t length)
{
	int status = read(i2c->fd, data, length);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_i2c_write(peripheral_i2c_h i2c, uint8_t *data, uint32_t length)
{
	int status = write(i2c->fd, data, length);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_i2c_read_register_byte(peripheral_i2c_h i2c, uint8_t reg, uint8_t *data_out)
{
	int status;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_READ;
	data_arg.size = I2C_SMBUS_BYTE_DATA;
	data_arg.data = &data;
	data_arg.command = reg;

	status = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(status);

	*data_out = data.byte;

	return 0;
}

int peripheral_interface_i2c_write_register_byte(peripheral_i2c_h i2c, uint8_t reg, uint8_t data_in)
{
	int status;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_WRITE;
	data_arg.size = I2C_SMBUS_BYTE_DATA;
	data_arg.data = &data;
	data_arg.command = reg;

	data.byte = data_in;

	status = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_i2c_read_register_word(peripheral_i2c_h i2c, uint8_t reg, uint16_t *data_out)
{
	int status;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_READ;
	data_arg.size = I2C_SMBUS_WORD_DATA;
	data_arg.data = &data;
	data_arg.command = reg;

	status = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(status);

	*data_out = data.word;

	return 0;
}

int peripheral_interface_i2c_write_register_word(peripheral_i2c_h i2c, uint8_t reg, uint16_t data_in)
{
	int status;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_WRITE;
	data_arg.size = I2C_SMBUS_WORD_DATA;
	data_arg.data = &data;
	data_arg.command = reg;

	data.word = data_in;

	status = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(status);

	return 0;
}