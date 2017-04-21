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
#include <gio/gio.h>

#include "peripheral_io.h"
#include "peripheral_dbus.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"
#include "peripheral_io_gdbus.h"

PeripheralIoGdbusGpio *gpio_proxy = NULL;
PeripheralIoGdbusI2c *i2c_proxy = NULL;
PeripheralIoGdbusPwm *pwm_proxy = NULL;

void gpio_proxy_init(void)
{
	GError *error = NULL;

	if (gpio_proxy != NULL)
		return;

	gpio_proxy = peripheral_io_gdbus_gpio_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_DBUS_NAME,
		PERIPHERAL_DBUS_GPIO_PATH,
		NULL,
		&error);
}

void i2c_proxy_init(void)
{
	GError *error = NULL;

	if (i2c_proxy != NULL)
		return;

	i2c_proxy = peripheral_io_gdbus_i2c_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_DBUS_NAME,
		PERIPHERAL_DBUS_I2C_PATH,
		NULL,
		&error);
}

void pwm_proxy_init(void)
{
	GError *error = NULL;

	if (pwm_proxy != NULL)
		return;

	pwm_proxy = peripheral_io_gdbus_pwm_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_DBUS_NAME,
		PERIPHERAL_DBUS_PWM_PATH,
		NULL,
		&error);
}

void gpio_proxy_deinit()
{
	gpio_proxy = NULL;
}

void i2c_proxy_deinit()
{
	i2c_proxy = NULL;
}

void pwm_proxy_deinit()
{
	pwm_proxy = NULL;
}

int peripheral_dbus_gpio_open(peripheral_gpio_h gpio)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (gpio_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_gpio_call_open_sync(
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

int peripheral_dbus_gpio_close(peripheral_gpio_h gpio)
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

int peripheral_dbus_gpio_get_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e *direction)
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

	return ret;
}

int peripheral_dbus_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
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

	return ret;
}

int peripheral_dbus_gpio_read(peripheral_gpio_h gpio, int *value)
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

int peripheral_dbus_gpio_write(peripheral_gpio_h gpio, int value)
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

int peripheral_dbus_gpio_get_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e *edge)
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

	return ret;
}

int peripheral_dbus_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
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

	return ret;
}

int peripheral_dbus_i2c_init(peripheral_i2c_h i2c, int bus)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (i2c_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_i2c_call_init_sync(
			i2c_proxy,
			bus,
			&i2c->fd,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_dbus_i2c_stop(peripheral_i2c_h i2c)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (i2c_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_i2c_call_stop_sync(
			i2c_proxy,
			i2c->fd,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_dbus_i2c_set_address(peripheral_i2c_h i2c, int address)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (i2c_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_i2c_call_set_address_sync(
			i2c_proxy,
			i2c->fd,
			address,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	if (ret != PERIPHERAL_ERROR_NONE)
		_E("%s failed, ret = %d", __func__, ret);

	return ret;
}

int peripheral_dbus_i2c_read(peripheral_i2c_h i2c, uint8_t *data, int length)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GVariant *data_array;
	GVariantIter *iter;
	guint8 str;
	int i = 0;

	if (i2c_proxy == NULL || data == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_i2c_call_read_sync(
			i2c_proxy,
			i2c->fd,
			length,
			&data_array,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	g_variant_get(data_array, "a(y)", &iter);
	while (g_variant_iter_loop(iter, "(y)", &str)) {
		data[i] = str;
		if (i++ == length) break;
	}
	g_variant_iter_free(iter);

	return ret;
}

int peripheral_dbus_i2c_write(peripheral_i2c_h i2c, uint8_t *data, int length)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	GVariantBuilder *builder;
	GVariant *g_data;
	int i = 0;

	if (i2c_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	builder = g_variant_builder_new(G_VARIANT_TYPE("a(y)"));

	for (i = 0; i < length; i++)
		g_variant_builder_add(builder, "(y)", data[i]);
	g_variant_builder_add(builder, "(y)", 0x00);

	g_data = g_variant_new("a(y)", builder);
	g_variant_builder_unref(builder);

	if (peripheral_io_gdbus_i2c_call_write_sync(
			i2c_proxy,
			i2c->fd,
			length,
			g_data,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_dbus_pwm_open(peripheral_pwm_context_h dev, int device, int channel)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	/* TODO: Need to reorganize arguments */
	if (peripheral_io_gdbus_pwm_call_open_sync(
			pwm_proxy,
			device,
			channel,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_dbus_pwm_close(peripheral_pwm_context_h dev)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	/* TODO: Need to reorganize arguments */
	if (peripheral_io_gdbus_pwm_call_close_sync(
			pwm_proxy,
			dev->device,
			dev->channel,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_dbus_pwm_get_duty_cycle(peripheral_pwm_context_h dev, int *duty_cycle)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	/* TODO: Need to reorganize arguments */
	if (peripheral_io_gdbus_pwm_call_get_duty_cycle_sync(
			pwm_proxy,
			dev->device,
			dev->channel,
			duty_cycle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}
int peripheral_dbus_pwm_set_duty_cycle(peripheral_pwm_context_h dev, int duty_cycle)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	/* TODO: Need to reorganize arguments */
	if (peripheral_io_gdbus_pwm_call_set_duty_cycle_sync(
			pwm_proxy,
			dev->device,
			dev->channel,
			duty_cycle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_dbus_pwm_get_period(peripheral_pwm_context_h dev, int *period)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	/* TODO: Need to reorganize arguments */
	if (peripheral_io_gdbus_pwm_call_get_period_sync(
			pwm_proxy,
			dev->device,
			dev->channel,
			period,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_dbus_pwm_set_period(peripheral_pwm_context_h dev, int period)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	/* TODO: Need to reorganize arguments */
	if (peripheral_io_gdbus_pwm_call_set_period_sync(
			pwm_proxy,
			dev->device,
			dev->channel,
			period,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_dbus_pwm_set_enable(peripheral_pwm_context_h dev, peripheral_pwm_state_e enable)
{
	GError *error = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	/* TODO: Need to reorganize arguments */
	if (peripheral_io_gdbus_pwm_call_set_enable_sync(
			pwm_proxy,
			dev->device,
			dev->channel,
			enable,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s\n", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}
