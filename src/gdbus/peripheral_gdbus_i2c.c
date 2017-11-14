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

static int __i2c_proxy_init()
{
	GError *error = NULL;

	if (i2c_proxy != NULL) {
		_E("I2c proxy is already created");
		g_object_ref(i2c_proxy);
		return PERIPHERAL_ERROR_NONE;
	}

	i2c_proxy = peripheral_io_gdbus_i2c_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_I2C_PATH,
		NULL,
		&error);

	if (i2c_proxy == NULL) {
		_E("Failed to create i2c proxy : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

static void __i2c_proxy_deinit()
{
	if (i2c_proxy) {
		g_object_unref(i2c_proxy);
		if (!G_IS_OBJECT(i2c_proxy))
			i2c_proxy = NULL;
	}
}

int peripheral_gdbus_i2c_open(peripheral_i2c_h i2c, int bus, int address)
{
	int ret;
	GError *error = NULL;
	GUnixFDList *fd_list = NULL;

	ret = __i2c_proxy_init();
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

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
		_E("Failed to request daemon to i2c open : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	// TODO : If ret is not PERIPHERAL_ERROR_NONE, fd list it NULL from daemon.
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	i2c->fd = g_unix_fd_list_get(fd_list, I2C_FD_INDEX, &error);
	if (i2c->fd < 0) {
		_E("Failed to get fd for i2c : %s", error->message);
		g_error_free(error);
	}

	g_object_unref(fd_list);

	return ret;
}

int peripheral_gdbus_i2c_close(peripheral_i2c_h i2c)
{
	int ret;
	GError *error = NULL;

	if (i2c_proxy == NULL) {
		_E("Can't try to i2c close because i2c proxy is NULL.");
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	if (peripheral_io_gdbus_i2c_call_close_sync(
			i2c_proxy,
			i2c->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Failed to request daemon to i2c close : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	// TODO : If the return value is not PERIPHERAL_ERROR_NONE, the daemon returns status before close request.
	if (ret == PERIPHERAL_ERROR_NONE)
		__i2c_proxy_deinit();

	return ret;
}
