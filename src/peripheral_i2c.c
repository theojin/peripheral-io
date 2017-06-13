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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "peripheral_io.h"
#include "peripheral_gdbus_i2c.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

/* i2c_smbus_xfer read or write markers */
#define I2C_SMBUS_READ	1
#define I2C_SMBUS_WRITE	0

/* SMBus transaction types */
#define I2C_SMBUS_QUICK		    0
#define I2C_SMBUS_BYTE		    1
#define I2C_SMBUS_BYTE_DATA	    2
#define I2C_SMBUS_WORD_DATA	    3

int peripheral_i2c_open(int bus, int address, peripheral_i2c_h *i2c)
{
	peripheral_i2c_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(bus < 0 || address < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	handle = (peripheral_i2c_h)malloc(sizeof(struct _peripheral_i2c_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_i2c_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	i2c_proxy_init();

	ret = peripheral_gdbus_i2c_open(handle, bus, address);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to open i2c communication, ret : %d", ret);
		free(handle);
		handle = NULL;
	}
	*i2c = handle;

	return ret;
}

int peripheral_i2c_close(peripheral_i2c_h i2c)
{
	int ret;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	ret = peripheral_gdbus_i2c_close(i2c);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to close i2c communcation, ret : %d", ret);
	i2c_proxy_deinit();

	free(i2c);
	i2c = NULL;

	return ret;
}

int peripheral_i2c_read(peripheral_i2c_h i2c, uint8_t *data, int length)
{
	int ret;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");
	RETVM_IF(data == NULL || length < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	ret = peripheral_gdbus_i2c_read(i2c, data, length);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to read data from device, ret : %d", ret);

	return ret;
}

int peripheral_i2c_write(peripheral_i2c_h i2c, uint8_t *data, int length)
{
	int ret;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");
	RETVM_IF(data == NULL || length < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	ret = peripheral_gdbus_i2c_write(i2c, data, length);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to write data to device, ret : %d", ret);

	return ret;
}

int peripheral_i2c_read_byte(peripheral_i2c_h i2c, uint8_t *data)
{
	int ret;
	uint16_t w_data, dummy = 0;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	ret = peripheral_gdbus_i2c_smbus_ioctl(i2c, I2C_SMBUS_READ, 0x0, I2C_SMBUS_BYTE, dummy, &w_data);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to read, ret : %d", ret);

	*data = (uint8_t)w_data;

	return ret;
}

int peripheral_i2c_write_byte(peripheral_i2c_h i2c, uint8_t data)
{
	int ret = PERIPHERAL_ERROR_NONE;
	uint16_t dummy = 0;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	ret = peripheral_gdbus_i2c_smbus_ioctl(i2c, I2C_SMBUS_WRITE, dummy, I2C_SMBUS_BYTE, (uint16_t)data, &dummy);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to write, ret : %d", ret);

	return ret;
}

int peripheral_i2c_read_register_byte(peripheral_i2c_h i2c, uint8_t address, uint8_t *data)
{
	int ret;
	uint16_t w_data, dummy = 0;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	ret = peripheral_gdbus_i2c_smbus_ioctl(i2c, I2C_SMBUS_READ, address, I2C_SMBUS_BYTE_DATA, dummy, &w_data);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Smbus transaction failed, ret : %d", ret);

	*data = (uint8_t)w_data;

	return ret;
}

int peripheral_i2c_write_register_byte(peripheral_i2c_h i2c, uint8_t address, uint8_t data)
{
	int ret;
	uint16_t dummy = 0;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	ret = peripheral_gdbus_i2c_smbus_ioctl(i2c, I2C_SMBUS_WRITE, address, I2C_SMBUS_BYTE_DATA, (uint16_t)data, &dummy);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Smbus transaction failed, ret : %d", ret);

	return ret;
}

int peripheral_i2c_read_register_word(peripheral_i2c_h i2c, uint8_t address, uint16_t *data)
{
	int ret;
	uint16_t dummy = 0, data_out;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	ret = peripheral_gdbus_i2c_smbus_ioctl(i2c, I2C_SMBUS_READ, address, I2C_SMBUS_WORD_DATA, dummy, &data_out);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Smbus transaction failed, ret : %d", ret);

	*data = data_out;

	return ret;
}

int peripheral_i2c_write_register_word(peripheral_i2c_h i2c, uint8_t address, uint16_t data)
{
	int ret;
	uint16_t dummy = 0;

	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	ret = peripheral_gdbus_i2c_smbus_ioctl(i2c, I2C_SMBUS_WRITE, address, I2C_SMBUS_WORD_DATA, data, &dummy);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Smbus transaction failed, ret : %d", ret);

	return ret;
}
