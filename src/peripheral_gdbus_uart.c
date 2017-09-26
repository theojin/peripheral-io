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

#include "peripheral_io.h"
#include "peripheral_gdbus.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"
#include "peripheral_io_gdbus.h"

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

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_open_sync(
			uart_proxy,
			port,
			&uart->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

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

int peripheral_gdbus_uart_set_baud_rate(peripheral_uart_h uart, peripheral_uart_baud_rate_e baud)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_set_baud_rate_sync(
			uart_proxy,
			uart->handle,
			baud,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_uart_set_byte_size(peripheral_uart_h uart, peripheral_uart_byte_size_e byte_size)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_set_byte_size_sync(
			uart_proxy,
			uart->handle,
			byte_size,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_uart_set_parity(peripheral_uart_h uart, peripheral_uart_parity_e parity)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_set_parity_sync(
			uart_proxy,
			uart->handle,
			parity,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_uart_set_stop_bits(peripheral_uart_h uart, peripheral_uart_stop_bits_e stop_bits)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_set_stop_bits_sync(
			uart_proxy,
			uart->handle,
			stop_bits,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_uart_set_flow_control(peripheral_uart_h uart, bool xonxoff, bool rtscts)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_set_flow_control_sync(
			uart_proxy,
			uart->handle,
			xonxoff,
			rtscts,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_uart_read(peripheral_uart_h uart, uint8_t *data, int length)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GVariant *data_array;
	GVariantIter *iter;
	guint8 str;
	int i = 0;

	if (uart_proxy == NULL || data == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_uart_call_read_sync(
			uart_proxy,
			uart->handle,
			length,
			&data_array,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	g_variant_get(data_array, "a(y)", &iter);
	while (g_variant_iter_loop(iter, "(y)", &str)) {
		data[i] = str;
		if (i++ == length) break;
	}
	g_variant_iter_free(iter);
	g_variant_unref(data_array);

	return ret;
}

int peripheral_gdbus_uart_write(peripheral_uart_h uart, uint8_t *data, int length)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GVariantBuilder *builder;
	GVariant *g_data;
	int i = 0;

	if (uart_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	builder = g_variant_builder_new(G_VARIANT_TYPE("a(y)"));

	for (i = 0; i < length; i++)
		g_variant_builder_add(builder, "(y)", data[i]);
	g_variant_builder_add(builder, "(y)", 0x00);

	g_data = g_variant_new("a(y)", builder);
	g_variant_builder_unref(builder);

	if (peripheral_io_gdbus_uart_call_write_sync(
			uart_proxy,
			uart->handle,
			length,
			g_data,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}
