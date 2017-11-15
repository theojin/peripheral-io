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

#include "peripheral_gdbus_uart.h"

#define UART_FD_INDEX 0

static PeripheralIoGdbusUart *uart_proxy = NULL;

static int __uart_proxy_init()
{
	GError *error = NULL;

	if (uart_proxy != NULL) {
		_E("Uart proxy is already created");
		g_object_ref(uart_proxy);
		return PERIPHERAL_ERROR_NONE;
	}

	uart_proxy = peripheral_io_gdbus_uart_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_UART_PATH,
		NULL,
		&error);

	if (uart_proxy == NULL) {
		_E("Failed to create uart proxy : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

static void __uart_proxy_deinit()
{
	if (uart_proxy) {
		g_object_unref(uart_proxy);
		if (!G_IS_OBJECT(uart_proxy))
			uart_proxy = NULL;
	}
}

int peripheral_gdbus_uart_open(peripheral_uart_h uart, int port)
{
	int ret;
	GError *error = NULL;
	GUnixFDList *fd_list = NULL;

	ret = __uart_proxy_init();
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	if (peripheral_io_gdbus_uart_call_open_sync(
			uart_proxy,
			port,
			NULL,
			&uart->handle,
			&ret,
			&fd_list,
			NULL,
			&error) == FALSE) {
		_E("Failed to request daemon to uart open : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	// TODO : If ret is not PERIPHERAL_ERROR_NONE, fd list it NULL from daemon.
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	uart->fd = g_unix_fd_list_get(fd_list, UART_FD_INDEX, &error);
	if (uart->fd < 0) {
		_E("Failed to get fd for uart : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	g_object_unref(fd_list);

	return ret;
}

int peripheral_gdbus_uart_close(peripheral_uart_h uart)
{
	int ret;
	GError *error = NULL;

	if (uart_proxy == NULL) {
		_E("Can't try to uart close because uart proxy is NULL.");
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	if (peripheral_io_gdbus_uart_call_close_sync(
			uart_proxy,
			uart->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Failed to request daemon to uart close : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	// TODO : If the return value is not PERIPHERAL_ERROR_NONE, the daemon returns status before close request.
	if (ret == PERIPHERAL_ERROR_NONE)
		__uart_proxy_deinit();

	return ret;
}
