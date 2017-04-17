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

GDBusConnection *connection = NULL;

int set_dbus_connection(void)
{
	GError *error = NULL;

	if (connection)
		return PERIPHERAL_ERROR_NONE;

	connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
	if (error) {
		_E("gdbus error occurred (%s)", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	if (!connection) {
		_E("Failed to get gdbus connection ");
		return PERIPHERAL_ERROR_UNKNOWN;
	} else {
		//Sets whether the process should be terminated when connection is closed by the remote peer
		g_dbus_connection_set_exit_on_close(connection, FALSE); //FALSE shareable connection is NOT closed by the remote peer
	}

	return PERIPHERAL_ERROR_NONE;
}

void unset_dbus_connection(void)
{
	if (connection) {
		g_object_unref(connection);
		connection = NULL;
	}
}

GDBusConnection *get_dbus_connection(void)
{
	return connection;
}

int peripheral_dbus_gpio(peripheral_gpio_h gpio, char * sensorid, char *funcname, int write_value, int *read_value)
{
	GError *error = NULL;

	GVariant *ret_value = NULL;
	gint32 read = 0;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	error = NULL;

	ret_value = g_dbus_connection_call_sync(connection,
										PERIPHERAL_DBUS_NAME,
										PERIPHERAL_DBUS_PATH,
										PERIPHERAL_DBUS_INTERFACE,
										sensorid,
										g_variant_new("(siiii)", funcname, gpio->pin, gpio->direction, gpio->edge, write_value),
										G_VARIANT_TYPE("(iiiii)"),
										G_DBUS_CALL_FLAGS_NONE,
										-1,
										NULL,
										&error);

	if (ret_value == NULL) {
		g_printerr("Error invoking %s () : %s\n", sensorid, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	g_variant_get(ret_value, "(iiiii)", &gpio->pin, &gpio->direction, &gpio->edge, &read, &ret);
	g_variant_unref(ret_value);

	if (read_value != 0)
		(*read_value) = read;

	return ret;

}

int peripheral_dbus_i2c(peripheral_i2c_context_h dev, char * sensorid, char *funcname, int value, unsigned char * data, int addr)
{
	GError *error = NULL;
	GVariant *ret_value = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;
	GVariantBuilder *builder;
	guint8 str;
	GVariantIter *ret_data;

	builder = g_variant_builder_new(G_VARIANT_TYPE("ay"));
	if (data == NULL) {
		g_variant_builder_add(builder, "y", 0x10);
		g_variant_builder_add(builder, "y", 0x00);
	} else {
		int i = 0;
		for (i = 0; i < value; i++)
			g_variant_builder_add(builder, "y", data[i]);
		g_variant_builder_add(builder, "y", 0x00);
	}

	ret_value = g_dbus_connection_call_sync(connection,
										PERIPHERAL_DBUS_NAME,
										PERIPHERAL_DBUS_PATH,
										PERIPHERAL_DBUS_INTERFACE,
										sensorid,
										g_variant_new("(siiayi)", funcname, value, dev->fd, builder, addr),
										G_VARIANT_TYPE("(iayi)"),
										G_DBUS_CALL_FLAGS_NONE,
										-1,
										NULL,
										&error);

	g_variant_builder_unref(builder);

	if (ret_value == NULL) {
		g_printerr("Error invoking %s () : %s\n", sensorid, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	g_variant_get(ret_value, "(iayi)", &(dev->fd), &ret_data, &ret);
	g_variant_unref(ret_value);

	if (data != NULL) {
		int i = 0;
		while (g_variant_iter_loop(ret_data, "y", &str)) {
			data[i] = str;
			i++;
			if (i == value)
				break;
		}
	}

	return ret;
}

int peripheral_dbus_pwm(peripheral_pwm_context_h dev, char * sensorid, char *funcname)
{
	GError *error = NULL;
	GVariant *ret_value = NULL;
	gint32 ret = PERIPHERAL_ERROR_NONE;

	ret_value = g_dbus_connection_call_sync(connection,
										PERIPHERAL_DBUS_NAME,
										PERIPHERAL_DBUS_PATH,
										PERIPHERAL_DBUS_INTERFACE,
										sensorid,
										g_variant_new("(siiiii)", funcname, dev->device, dev->channel, dev->period, dev->duty_cycle, dev->enabled),
										G_VARIANT_TYPE("(iii)"),
										G_DBUS_CALL_FLAGS_NONE,
										-1,
										NULL,
										&error);
	if (ret_value == NULL) {
		g_printerr("Error invoking %s () : %s\n", sensorid, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	g_variant_get(ret_value, "(iii)", &dev->period, &dev->duty_cycle, &ret);
	g_variant_unref(ret_value);

	return ret;
}
