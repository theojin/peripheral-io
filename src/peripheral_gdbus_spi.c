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

PeripheralIoGdbusSpi *spi_proxy = NULL;

void spi_proxy_init(void)
{
	GError *error = NULL;

	if (spi_proxy != NULL) {
		g_object_ref(spi_proxy);
		return;
	}

	spi_proxy = peripheral_io_gdbus_spi_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_SPI_PATH,
		NULL,
		&error);
}

void spi_proxy_deinit()
{
	if (spi_proxy) {
		g_object_unref(spi_proxy);
		if (!G_IS_OBJECT(spi_proxy))
			spi_proxy = NULL;
	}
}

int peripheral_gdbus_spi_open(peripheral_spi_h spi, int bus, int cs)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_open_sync(
			spi_proxy,
			bus,
			cs,
			&spi->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_spi_close(peripheral_spi_h spi)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_close_sync(
			spi_proxy,
			spi->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_spi_set_mode(peripheral_spi_h spi, peripheral_spi_mode_e mode)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_set_mode_sync(
			spi_proxy,
			spi->handle,
			(guchar)mode,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_spi_get_mode(peripheral_spi_h spi, peripheral_spi_mode_e *mode)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	guchar value;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_get_mode_sync(
			spi_proxy,
			spi->handle,
			&value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	if (value <= PERIPHERAL_SPI_MODE_3)
		*mode = value;
	else
		_E("Invalid mode : %d", value);

	return ret;
}

int peripheral_gdbus_spi_set_lsb_first(peripheral_spi_h spi, bool lsb)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_set_lsb_first_sync(
			spi_proxy,
			spi->handle,
			lsb,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_spi_get_lsb_first(peripheral_spi_h spi, bool *lsb)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	gboolean value;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_get_lsb_first_sync(
			spi_proxy,
			spi->handle,
			&value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	*lsb = value ? true : false;

	return ret;
}

int peripheral_gdbus_spi_set_bits(peripheral_spi_h spi, unsigned char bits)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_set_bits_sync(
			spi_proxy,
			spi->handle,
			bits,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_spi_get_bits(peripheral_spi_h spi, unsigned char *bits)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	guchar value;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_get_bits_sync(
			spi_proxy,
			spi->handle,
			&value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	*bits = (unsigned char)value;

	return ret;
}

int peripheral_gdbus_spi_set_frequency(peripheral_spi_h spi, unsigned int freq)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_set_frequency_sync(
			spi_proxy,
			spi->handle,
			freq,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_spi_get_frequency(peripheral_spi_h spi, unsigned int *freq)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	guint value;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_get_frequency_sync(
			spi_proxy,
			spi->handle,
			&value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	*freq = (unsigned int)value;

	return ret;
}

int peripheral_gdbus_spi_read(peripheral_spi_h spi, unsigned char *data, int length)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GVariant *data_array;
	GVariantIter *iter;
	guint8 str;
	int i = 0;

	if (spi_proxy == NULL || data == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_read_sync(
			spi_proxy,
			spi->handle,
			length,
			&data_array,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
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

int peripheral_gdbus_spi_write(peripheral_spi_h spi, unsigned char *data, int length)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GVariantBuilder *builder;
	GVariant *data_array;
	int i = 0;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	builder = g_variant_builder_new(G_VARIANT_TYPE("a(y)"));

	for (i = 0; i < length; i++)
		g_variant_builder_add(builder, "(y)", data[i]);
	g_variant_builder_add(builder, "(y)", 0x00);

	data_array = g_variant_new("a(y)", builder);
	g_variant_builder_unref(builder);

	if (peripheral_io_gdbus_spi_call_write_sync(
			spi_proxy,
			spi->handle,
			length,
			data_array,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_spi_read_write(peripheral_spi_h spi, unsigned char *tx_data, unsigned char *rx_data, int length)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GVariantBuilder *builder;
	GVariant *rx_data_array;
	GVariant *tx_data_array;
	GVariantIter *iter;
	guint8 str;
	int i = 0;

	if (spi_proxy == NULL || !rx_data || !tx_data) return PERIPHERAL_ERROR_UNKNOWN;

	builder = g_variant_builder_new(G_VARIANT_TYPE("a(y)"));

	for (i = 0; i < length; i++)
		g_variant_builder_add(builder, "(y)", tx_data[i]);
	g_variant_builder_add(builder, "(y)", 0x00);

	tx_data_array = g_variant_new("a(y)", builder);
	g_variant_builder_unref(builder);

	if (peripheral_io_gdbus_spi_call_read_write_sync(
			spi_proxy,
			spi->handle,
			length,
			tx_data_array,
			&rx_data_array,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	i = 0;
	g_variant_get(rx_data_array, "a(y)", &iter);
	while (g_variant_iter_loop(iter, "(y)", &str)) {
		rx_data[i] = str;
		if (i++ == length) break;
	}
	g_variant_iter_free(iter);
	g_variant_unref(rx_data_array);

	return ret;
}
