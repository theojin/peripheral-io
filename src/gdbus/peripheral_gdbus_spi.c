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

#define SPI_FD_INDEX 0

static PeripheralIoGdbusSpi *spi_proxy = NULL;

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
	GUnixFDList *fd_list = NULL;

	if (spi_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_spi_call_open_sync(
			spi_proxy,
			bus,
			cs,
			NULL,
			&spi->handle,
			&ret,
			&fd_list,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	spi->fd = g_unix_fd_list_get(fd_list, SPI_FD_INDEX, &error);
	if (spi->fd < 0) {
		_E("Failed to get fd for spi : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	g_object_unref(fd_list);

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