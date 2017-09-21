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

static PeripheralIoGdbusPwm *pwm_proxy = NULL;

void pwm_proxy_init(void)
{
	GError *error = NULL;

	if (pwm_proxy != NULL) {
		g_object_ref(pwm_proxy);
		return;
	}

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
		if (!G_IS_OBJECT(pwm_proxy))
			pwm_proxy = NULL;
	}
}

int peripheral_gdbus_pwm_open(peripheral_pwm_h pwm, int chip, int pin)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_pwm_call_open_sync(
			pwm_proxy,
			chip,
			pin,
			&pwm->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_pwm_close(peripheral_pwm_h pwm)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_pwm_call_close_sync(
			pwm_proxy,
			pwm->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_pwm_set_period(peripheral_pwm_h pwm, int period)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_pwm_call_set_period_sync(
			pwm_proxy,
			pwm->handle,
			period,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_pwm_set_duty_cycle(peripheral_pwm_h pwm, int duty_cycle_ns)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_pwm_call_set_duty_cycle_sync(
			pwm_proxy,
			pwm->handle,
			duty_cycle_ns,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_pwm_set_polarity(peripheral_pwm_h pwm, peripheral_pwm_polarity_e polarity)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_pwm_call_set_polarity_sync(
			pwm_proxy,
			pwm->handle,
			polarity,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}

int peripheral_gdbus_pwm_set_enable(peripheral_pwm_h pwm, bool enable)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_pwm_call_set_enable_sync(
			pwm_proxy,
			pwm->handle,
			enable,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return ret;
}
