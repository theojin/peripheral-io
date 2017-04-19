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
#include "peripheral_dbus.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_NAME	"i2c"
int I2C_Addr = 0;

peripheral_i2c_h peripheral_i2c_init(int bus)
{
	peripheral_i2c_h i2c;
	int ret = PERIPHERAL_ERROR_NONE;

	assert(bus >= 0);

	/* Initialize peripheral_i2c_h */
	i2c = (peripheral_i2c_h)malloc(sizeof(struct _peripheral_i2c_s));

	if (i2c == NULL) {
		_E("Failed to allocate peripheral_i2c_h");
		return NULL;
	}

	if (!get_dbus_connection())
		set_dbus_connection();

	ret = peripheral_dbus_i2c(i2c, I2C_NAME, "INIT", bus, 0, I2C_Addr);

	if (ret != PERIPHERAL_ERROR_NONE) {
		free(i2c);
		_E("[PERIPHERAL] I2C init error\n");
		i2c = NULL;
	}

	return i2c;
}

int peripheral_i2c_stop(peripheral_i2c_h i2c)
{
	int ret = PERIPHERAL_ERROR_NONE;
	/* Free peripheral_i2c_h */

	if (i2c != NULL) {
		ret = peripheral_dbus_i2c(i2c, I2C_NAME, "STOP", 0, 0, I2C_Addr);

		free(i2c);
		i2c = NULL;
	}

	return ret;
}

int peripheral_i2c_set_address(peripheral_i2c_h i2c, int address)
{
	/* Set the i2c slave address */

	//I2C_Addr = address;
	return peripheral_dbus_i2c(i2c, I2C_NAME, "SET_ADDR", address, 0, I2C_Addr);
}

int peripheral_i2c_read(peripheral_i2c_h i2c, uint8_t *data, int length)
{
	/* Read i2c data */
	return peripheral_dbus_i2c(i2c, I2C_NAME, "READ", length, data, I2C_Addr);
}

int peripheral_i2c_write(peripheral_i2c_h i2c, uint8_t *data, int length)
{
	/* Write i2c data */
	return peripheral_dbus_i2c(i2c, I2C_NAME, "WRITE", length, data, I2C_Addr);
}

#ifdef __cplusplus
}
#endif
