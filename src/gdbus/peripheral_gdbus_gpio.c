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

#include "peripheral_gdbus_gpio.h"

#define GPIO_FD_INDEX_DIRECTION 0
#define GPIO_FD_INDEX_EDGE      1
#define GPIO_FD_INDEX_VALUE     2

static PeripheralIoGdbusGpio *gpio_proxy = NULL;

static int __gpio_proxy_init()
{
	GError *error = NULL;

	if (gpio_proxy != NULL) {
		_E("Gpio proxy is already created");
		g_object_ref(gpio_proxy);
		return PERIPHERAL_ERROR_NONE;
	}

	gpio_proxy = peripheral_io_gdbus_gpio_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_GPIO_PATH,
		NULL,
		&error);

	if (gpio_proxy == NULL) {
		_E("Failed to create gpio proxy : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

static void __gpio_proxy_deinit()
{
	if (gpio_proxy != NULL) {
		g_object_unref(gpio_proxy);
		if (!G_IS_OBJECT(gpio_proxy))
			gpio_proxy = NULL;
	}
}

int peripheral_gdbus_gpio_open(peripheral_gpio_h gpio)
{
	int ret;
	GError *error = NULL;
	GUnixFDList *fd_list = NULL;

	ret = __gpio_proxy_init();
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	if (peripheral_io_gdbus_gpio_call_open_sync(
			gpio_proxy,
			gpio->pin,
			NULL,
			&gpio->handle,
			&ret,
			&fd_list,
			NULL,
			&error) == FALSE) {
		_E("Failed to request daemon to gpio open : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	// TODO : If ret is not PERIPHERAL_ERROR_NONE, fd list it NULL from daemon.
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	gpio->fd_direction = g_unix_fd_list_get(fd_list, GPIO_FD_INDEX_DIRECTION, &error);
	if (gpio->fd_direction < 0) {
		_E("Failed to get fd for gpio direction : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	gpio->fd_edge = g_unix_fd_list_get(fd_list, GPIO_FD_INDEX_EDGE, &error);
	if (gpio->fd_edge < 0) {
		_E("Failed to get fd for gpio edge : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	gpio->fd_value = g_unix_fd_list_get(fd_list, GPIO_FD_INDEX_VALUE, &error);
	if (gpio->fd_value < 0) {
		_E("Failed to get fd for gpio value : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	g_object_unref(fd_list);

	return ret;
}

int peripheral_gdbus_gpio_close(peripheral_gpio_h gpio)
{
	int ret;
	GError *error = NULL;

	if (gpio_proxy == NULL) {
		_E("Can't try to gpio close because gpio proxy is NULL.");
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	if (peripheral_io_gdbus_gpio_call_close_sync(
			gpio_proxy,
			gpio->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Failed to request daemon to gpio close : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	// TODO : If the return value is not PERIPHERAL_ERROR_NONE, the daemon returns status before close request.
	if (ret == PERIPHERAL_ERROR_NONE)
		__gpio_proxy_deinit();

	return ret;
}