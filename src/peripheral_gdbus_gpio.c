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

extern int peripheral_gpio_isr_callback(int pin);
void handle_gpio_changed(PeripheralIoGdbusGpio *gpio, gint pin, gint state, gpointer user_data);

PeripheralIoGdbusGpio *gpio_proxy = NULL;

void gpio_proxy_init(void)
{
	GError *error = NULL;

	if (gpio_proxy != NULL)
		return;

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
			"gpio-changed",
			G_CALLBACK(handle_gpio_changed),
			NULL);
}

void gpio_proxy_deinit()
{
	if (gpio_proxy) {
		g_object_unref(gpio_proxy);
		gpio_proxy = NULL;
	}
}

void handle_gpio_changed(
		PeripheralIoGdbusGpio *gpio,
		gint pin,
		gint state,
		gpointer user_data)
{
	if (!gpio)
		return;

	_D("gpio=%d state=%d", pin, state);

	peripheral_gpio_isr_callback(pin);
}

int peripheral_gdbus_gpio_open(peripheral_gpio_h gpio)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_open_sync(
			gpio_proxy,
			gpio->pin,
			(gint*)&gpio->edge,
			(gint*)&gpio->direction,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
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
			gpio->pin,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_get_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e *direction)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_get_direction_sync(
			gpio_proxy,
			gpio->pin,
			(gint*)direction,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}
	gpio->direction = *direction;

	return ret;
}

int peripheral_gdbus_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_set_direction_sync(
			gpio_proxy,
			gpio->pin,
			direction,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}
	gpio->direction = direction;

	return ret;
}

int peripheral_gdbus_gpio_read(peripheral_gpio_h gpio, int *value)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_read_sync(
			gpio_proxy,
			gpio->pin,
			value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
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
			gpio->pin,
			value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_get_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e *edge)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_get_edge_mode_sync(
			gpio_proxy,
			gpio->pin,
			(int*)edge,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}
	gpio->edge = *edge;

	return ret;
}

int peripheral_gdbus_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_set_edge_mode_sync(
			gpio_proxy,
			gpio->pin,
			edge,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}
	gpio->edge = edge;

	return ret;
}

int peripheral_gdbus_gpio_register_cb(peripheral_gpio_h gpio, gpio_isr_cb callback, void *user_data)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_register_irq_sync(
			gpio_proxy,
			gpio->pin,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_gpio_unregister_cb(peripheral_gpio_h gpio)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_unregister_irq_sync(
			gpio_proxy,
			gpio->pin,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}
