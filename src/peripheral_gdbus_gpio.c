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

extern int peripheral_gpio_interrupted_cb_handler(int pin, int value, unsigned long long timestamp, int err);

static PeripheralIoGdbusGpio *gpio_proxy = NULL;

static void __peripheral_gpio_interrupted_cb(PeripheralIoGdbusGpio *gpio, gint pin, gint value, guint64 timestamp, gpointer user_data)
{
	int err = PERIPHERAL_ERROR_NONE;
	if (!gpio)
		err = PERIPHERAL_ERROR_IO_ERROR;

	peripheral_gpio_interrupted_cb_handler(pin, value, timestamp, err);
}

void gpio_proxy_init(void)
{
	GError *error = NULL;

	if (gpio_proxy != NULL) {
		g_object_ref(gpio_proxy);
		return;
	}

	gpio_proxy = peripheral_io_gdbus_gpio_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_GPIO_PATH,
		NULL,
		&error);
	if (gpio_proxy == NULL) {
		_E("Can not create gpio proxy : %s", error->message);
		g_error_free(error);
		return;
	}

	g_signal_connect(gpio_proxy,
			"interrupted-cb",
			G_CALLBACK(__peripheral_gpio_interrupted_cb),
			NULL);
}

void gpio_proxy_deinit()
{
	if (gpio_proxy) {
		g_object_unref(gpio_proxy);
		if (!G_IS_OBJECT(gpio_proxy))
			gpio_proxy = NULL;
	}
}

int peripheral_gdbus_gpio_open(peripheral_gpio_h gpio)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_open_sync(
			gpio_proxy,
			gpio->pin,
			&gpio->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_close(peripheral_gpio_h gpio)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_close_sync(
			gpio_proxy,
			gpio->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_set_direction_sync(
			gpio_proxy,
			gpio->handle,
			direction,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_set_edge_mode_sync(
			gpio_proxy,
			gpio->handle,
			edge,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_set_interrupted_cb(peripheral_gpio_h gpio, peripheral_gpio_interrupted_cb callback, void *user_data)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_set_interrupted_cb_sync(
			gpio_proxy,
			gpio->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_unset_interrupted_cb(peripheral_gpio_h gpio)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_unset_interrupted_cb_sync(
			gpio_proxy,
			gpio->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_read(peripheral_gpio_h gpio, int *value)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_read_sync(
			gpio_proxy,
			gpio->handle,
			value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_write(peripheral_gpio_h gpio, int value)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_write_sync(
			gpio_proxy,
			gpio->handle,
			value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}
