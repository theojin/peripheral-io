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

#define UART_FD_INDEX 0

static PeripheralIoGdbusUart *uart_proxy = NULL;

void uart_proxy_init(void)
{
	GError *error = NULL;

	if (uart_proxy != NULL) {
		g_object_ref(uart_proxy);
		return;
	}

	uart_proxy = peripheral_io_gdbus_uart_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_UART_PATH,
		NULL,
		&error);
}

void uart_proxy_deinit()
{
	if (uart_proxy) {
		g_object_unref(uart_proxy);
		if (!G_IS_OBJECT(uart_proxy))
			uart_proxy = NULL;
	}
}

int peripheral_gdbus_uart_open(peripheral_uart_h uart, int port)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GUnixFDList *fd_list = NULL;

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_open_sync(
			uart_proxy,
			port,
			NULL,
			&uart->handle,
			&ret,
			&fd_list,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

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
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_close_sync(
			uart_proxy,
			uart->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}