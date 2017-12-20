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

void peripheral_interface_i2c_close(peripheral_i2c_h i2c)
{
	close(i2c->fd);
}

/* It was developed temporarily because of the I2C Stub. */
static int peripheral_interface_i2c_read_buffer(peripheral_i2c_h i2c, uint8_t *data_out, uint32_t length)
{
	int ret;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_READ;
	data_arg.size = I2C_SMBUS_BYTE;
	data_arg.data = &data;
	data_arg.command = *data_out;

	ret = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(ret != 0);

	*data_out = data.byte;

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_i2c_read(peripheral_i2c_h i2c, uint8_t *data_out, uint32_t length)
{
	int ret = read(i2c->fd, data_out, length);
	if (ret != length)
		return peripheral_interface_i2c_read_buffer(i2c, data_out, length);

	return PERIPHERAL_ERROR_NONE;
}

/* It was developed temporarily because of the I2C Stub. */
static int peripheral_interface_i2c_write_buffer(peripheral_i2c_h i2c, uint8_t *data_in, uint32_t length)
{
	int ret;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_WRITE;
	data_arg.size = I2C_SMBUS_BYTE;
	data_arg.data = &data;
	data_arg.command = *data_in;

	ret = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_i2c_write(peripheral_i2c_h i2c, uint8_t *data_in, uint32_t length)
{
	int ret = write(i2c->fd, data_in, length);
	if (ret != length)
		return peripheral_interface_i2c_write_buffer(i2c, data_in, length);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_i2c_read_register_byte(peripheral_i2c_h i2c, uint8_t reg, uint8_t *data_out)
{
	int ret;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_READ;
	data_arg.size = I2C_SMBUS_BYTE_DATA;
	data_arg.data = &data;
	data_arg.command = reg;

	ret = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(ret != 0);

	*data_out = data.byte;

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_i2c_write_register_byte(peripheral_i2c_h i2c, uint8_t reg, uint8_t data_in)
{
	int ret;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_WRITE;
	data_arg.size = I2C_SMBUS_BYTE_DATA;
	data_arg.data = &data;
	data_arg.command = reg;

	data.byte = data_in;

	ret = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_i2c_read_register_word(peripheral_i2c_h i2c, uint8_t reg, uint16_t *data_out)
{
	int ret;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_READ;
	data_arg.size = I2C_SMBUS_WORD_DATA;
	data_arg.data = &data;
	data_arg.command = reg;

	ret = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(ret != 0);

	*data_out = data.word;

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_i2c_write_register_word(peripheral_i2c_h i2c, uint8_t reg, uint16_t data_in)
{
	int ret;

	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data data;

	memset(&data, 0x0, sizeof(data.block));

	data_arg.read_write = I2C_SMBUS_WRITE;
	data_arg.size = I2C_SMBUS_WORD_DATA;
	data_arg.data = &data;
	data_arg.command = reg;

	data.word = data_in;

	ret = ioctl(i2c->fd, I2C_SMBUS, &data_arg);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}