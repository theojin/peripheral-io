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
#include <gio/gunixfdlist.h>

#include "peripheral_io.h"
#include "peripheral_gdbus.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"
#include "peripheral_io_gdbus.h"

#define I2C_FD_INDEX 0

static PeripheralIoGdbusI2c *i2c_proxy = NULL;

void i2c_proxy_init(void)
{
	GError *error = NULL;

	if (i2c_proxy != NULL) {
		g_object_ref(i2c_proxy);
		return;
	}

	i2c_proxy = peripheral_io_gdbus_i2c_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_I2C_PATH,
		NULL,
		&error);
}

void i2c_proxy_deinit()
{
	if (i2c_proxy) {
		g_object_unref(i2c_proxy);
		if (!G_IS_OBJECT(i2c_proxy))
			i2c_proxy = NULL;
	}
}

int peripheral_gdbus_i2c_open(peripheral_i2c_h i2c, int bus, int address)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GUnixFDList *fd_list = NULL;

	if (i2c_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_i2c_call_open_sync(
			i2c_proxy,
			bus,
			address,
			NULL,
			&i2c->handle,
			&ret,
			&fd_list,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	i2c->fd = g_unix_fd_list_get(fd_list, I2C_FD_INDEX, &error);
	if (i2c->fd < 0) {
		_E("Failed to get fd for i2c : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	g_object_unref(fd_list);

	return ret;
}

int peripheral_gdbus_i2c_close(peripheral_i2c_h i2c)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (i2c_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_i2c_call_close_sync(
			i2c_proxy,
			i2c->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}