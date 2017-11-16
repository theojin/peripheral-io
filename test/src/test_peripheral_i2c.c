/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
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
#include <string.h>
#include <peripheral_io.h>
#include "test_peripheral_i2c.h"

#define I2C_BUS 4
#define I2C_BUS_INVALID -99
#define I2C_ADDRESS 0x39
#define I2C_ADDRESS_INVALID -99
#define I2C_BUFFER_LEN 10
#define I2C_BUFFER_VALUE 0x00
#define I2C_REGISTER 0x00

static bool g_feature = true;
static int bus;
static int address;

int test_peripheral_io_i2c_initialize(char *model, bool feature)
{
	g_feature = feature;

	if ((!strcmp(model, "rpi3")) || (!strcmp(model, "artik")))
		bus = I2C_BUS;
	else
		return PERIPHERAL_ERROR_NO_DEVICE;

	address = I2C_ADDRESS;

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_open_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_open_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_i2c_open(bus, address, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_open_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_open(I2C_BUS_INVALID, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(I2C_BUS_INVALID, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_open_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_open(bus, I2C_ADDRESS_INVALID, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, I2C_ADDRESS_INVALID, &i2c_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_close_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_close_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_i2c_close(NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_close(NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_read_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	uint8_t buf[I2C_BUFFER_LEN];

	if (g_feature == false) {
		ret = peripheral_i2c_read(i2c_h, buf, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_read(i2c_h, buf, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_read_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint8_t buf[I2C_BUFFER_LEN];

	if (g_feature == false) {
		ret = peripheral_i2c_read(NULL, buf, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_read(NULL, buf, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_read_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_read(i2c_h, NULL, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_read(i2c_h, NULL, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_write_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	unsigned char buf[I2C_BUFFER_LEN] = {I2C_BUFFER_VALUE, };

	if (g_feature == false) {
		ret = peripheral_i2c_write(i2c_h, buf, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_write(i2c_h, buf, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_write_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	unsigned char buf[I2C_BUFFER_LEN] = {I2C_BUFFER_VALUE, };

	if (g_feature == false) {
		ret = peripheral_i2c_write(NULL, buf, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_write(NULL, buf, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_write_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_write(i2c_h, NULL, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_write(i2c_h, NULL, I2C_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_read_register_byte_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	uint8_t data;

	if (g_feature == false) {
		ret = peripheral_i2c_read_register_byte(i2c_h, I2C_REGISTER, &data);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_read_register_byte(i2c_h, I2C_REGISTER, &data);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_read_register_byte_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint8_t data;

	if (g_feature == false) {
		ret = peripheral_i2c_read_register_byte(NULL, I2C_REGISTER, &data);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_read_register_byte(NULL, I2C_REGISTER, &data);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}


int test_peripheral_io_i2c_peripheral_i2c_read_register_byte_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_read_register_byte(i2c_h, I2C_REGISTER, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_read_register_byte(i2c_h, I2C_REGISTER, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_write_register_byte_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_write_register_byte(i2c_h, I2C_REGISTER, I2C_BUFFER_VALUE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_write_register_byte(i2c_h, I2C_REGISTER, I2C_BUFFER_VALUE);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_write_register_byte_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_i2c_write_register_byte(NULL, I2C_REGISTER, I2C_BUFFER_VALUE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_write_register_byte(NULL, I2C_REGISTER, I2C_BUFFER_VALUE);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_read_register_word_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	uint16_t data;

	if (g_feature == false) {
		ret = peripheral_i2c_read_register_word(i2c_h, I2C_REGISTER, &data);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_read_register_word(i2c_h, I2C_REGISTER, &data);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_read_register_word_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint16_t data;

	if (g_feature == false) {
		ret = peripheral_i2c_read_register_word(NULL, I2C_REGISTER, &data);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_read_register_word(NULL, I2C_REGISTER, &data);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}


int test_peripheral_io_i2c_peripheral_i2c_read_register_word_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_read_register_word(i2c_h, I2C_REGISTER, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_read_register_word(i2c_h, I2C_REGISTER, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}


int test_peripheral_io_i2c_peripheral_i2c_write_register_word_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_i2c_h i2c_h = NULL;

	if (g_feature == false) {
		ret = peripheral_i2c_write_register_word(i2c_h, I2C_REGISTER, I2C_BUFFER_VALUE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_open(bus, address, &i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_i2c_write_register_word(i2c_h, I2C_REGISTER, I2C_BUFFER_VALUE);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_i2c_close(i2c_h);
			return ret;
		}

		ret = peripheral_i2c_close(i2c_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_i2c_peripheral_i2c_write_register_word_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_i2c_write_register_word(NULL, I2C_REGISTER, I2C_BUFFER_VALUE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_i2c_write_register_word(NULL, I2C_REGISTER, I2C_BUFFER_VALUE);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}
