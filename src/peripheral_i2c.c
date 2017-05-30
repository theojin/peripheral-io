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

int peripheral_i2c_open(int bus, int address, peripheral_i2c_h *i2c)
{
	peripheral_i2c_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	if (bus < 0)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	handle = (peripheral_i2c_h)malloc(sizeof(struct _peripheral_i2c_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_i2c_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	i2c_proxy_init();

	ret = peripheral_gdbus_i2c_open(handle, bus, address);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("[PERIPHERAL] I2C init error\n");
		free(handle);
		handle = NULL;
	}
	*i2c = handle;

	return ret;
}

int peripheral_i2c_close(peripheral_i2c_h i2c)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (i2c == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_gdbus_i2c_close(i2c);
	i2c_proxy_deinit();

	free(i2c);
	i2c = NULL;

	return ret;
}

int peripheral_i2c_read(peripheral_i2c_h i2c, uint8_t *data, int length)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (i2c == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_gdbus_i2c_read(i2c, data, length);
	/*
	_D("I2C read data : ");
	for (int i = 0 ; i < length ; i++)
		_D("[%02x]", data[i]);
	*/
	return ret;
}

int peripheral_i2c_write(peripheral_i2c_h i2c, uint8_t *data, int length)
{
	if (i2c == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_i2c_write(i2c, data, length);
}

int peripheral_i2c_read_byte(peripheral_i2c_h i2c, uint8_t *data)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (i2c == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_gdbus_i2c_read(i2c, data, 0x1);

	return ret;
}

int peripheral_i2c_write_byte(peripheral_i2c_h i2c, uint8_t data)
{
	if (i2c == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_i2c_write(i2c, &data, 0x1);
}
