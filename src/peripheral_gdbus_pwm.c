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

PeripheralIoGdbusPwm *pwm_proxy = NULL;

void pwm_proxy_init(void)
{
	GError *error = NULL;

	if (pwm_proxy != NULL)
		return;

	pwm_proxy = peripheral_io_gdbus_pwm_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_PWM_PATH,
		NULL,
		&error);
}

void pwm_proxy_deinit()
{
	if (pwm_proxy) {
		g_object_unref(pwm_proxy);
		pwm_proxy = NULL;
	}
}

int peripheral_gdbus_pwm_open(peripheral_pwm_h dev, int device, int channel)
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

int peripheral_gdbus_pwm_close(peripheral_pwm_h dev)
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

int peripheral_gdbus_pwm_set_period(peripheral_pwm_h dev, int period)
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

int peripheral_gdbus_pwm_get_period(peripheral_pwm_h dev, int *period)
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

int peripheral_gdbus_pwm_set_duty_cycle(peripheral_pwm_h dev, int duty_cycle)
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

int peripheral_gdbus_pwm_get_duty_cycle(peripheral_pwm_h dev, int *duty_cycle)
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

int peripheral_gdbus_pwm_set_enable(peripheral_pwm_h dev, peripheral_pwm_state_e enable)
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
