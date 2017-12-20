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

#include <stdlib.h>
#include <system_info.h>

#include "peripheral_io.h"
#include "peripheral_handle.h"
#include "peripheral_gdbus_i2c.h"
#include "peripheral_interface_i2c.h"
#include "peripheral_log.h"

#define PERIPHERAL_IO_I2C_FEATURE "http://tizen.org/feature/peripheral_io.i2c"

#define I2C_FEATURE_UNKNOWN -1
#define I2C_FEATURE_FALSE    0
#define I2C_FEATURE_TRUE     1

/* i2c_smbus_xfer read or write markers */
#define I2C_SMBUS_READ	1
#define I2C_SMBUS_WRITE	0

/* SMBus transaction types */
#define I2C_SMBUS_QUICK		    0
#define I2C_SMBUS_BYTE		    1
#define I2C_SMBUS_BYTE_DATA	    2
#define I2C_SMBUS_WORD_DATA	    3

static int i2c_feature = I2C_FEATURE_UNKNOWN;

static bool __is_feature_supported(void)
{
	int ret = SYSTEM_INFO_ERROR_NONE;
	bool feature = false;

	if (i2c_feature == I2C_FEATURE_UNKNOWN) {
		ret = system_info_get_platform_bool(PERIPHERAL_IO_I2C_FEATURE, &feature);
		RETVM_IF(ret != SYSTEM_INFO_ERROR_NONE, false, "Failed to get system info");

		i2c_feature = (feature ? I2C_FEATURE_TRUE : I2C_FEATURE_FALSE);
	}

	return (i2c_feature == I2C_FEATURE_TRUE ? true : false);
}

int peripheral_i2c_open(int bus, int address, peripheral_i2c_h *i2c)
{
	peripheral_i2c_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "I2C feature is not supported");
	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid i2c handle");
	RETVM_IF(bus < 0 || address < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	handle = (peripheral_i2c_h)malloc(sizeof(struct _peripheral_i2c_s));
	if (handle == NULL) {
		_E("Failed to allocate peripheral_i2c_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

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
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "I2C feature is not supported");
	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	ret = peripheral_gdbus_i2c_close(i2c);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to close i2c communcation, ret : %d", ret);
		return ret;
	}

	peripheral_interface_i2c_close(i2c);

	free(i2c);
	i2c = NULL;

	return ret;
}

int peripheral_i2c_read(peripheral_i2c_h i2c, uint8_t *data, uint32_t length)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "I2C feature is not supported");
	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");
	RETVM_IF(data == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_i2c_read(i2c, data, length);
}

int peripheral_i2c_write(peripheral_i2c_h i2c, uint8_t *data, uint32_t length)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "I2C feature is not supported");
	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");
	RETVM_IF(data == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_i2c_write(i2c, data, length);
}

int peripheral_i2c_read_register_byte(peripheral_i2c_h i2c, uint8_t reg, uint8_t *data)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "I2C feature is not supported");
	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");
	RETVM_IF(data == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_i2c_read_register_byte(i2c, reg, data);
}

int peripheral_i2c_write_register_byte(peripheral_i2c_h i2c, uint8_t reg, uint8_t data)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "I2C feature is not supported");
	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	return peripheral_interface_i2c_write_register_byte(i2c, reg, data);
}

int peripheral_i2c_read_register_word(peripheral_i2c_h i2c, uint8_t reg, uint16_t *data)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "I2C feature is not supported");
	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");
	RETVM_IF(data == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_i2c_read_register_word(i2c, reg, data);
}

int peripheral_i2c_write_register_word(peripheral_i2c_h i2c, uint8_t reg, uint16_t data)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "I2C feature is not supported");
	RETVM_IF(i2c == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "i2c handle is NULL");

	return peripheral_interface_i2c_write_register_word(i2c, reg, data);
}
