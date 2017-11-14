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

#define PWM_FD_INDEX_PERIOD      0
#define PWM_FD_INDEX_DUTY_CYCLE  1
#define PWM_FD_INDEX_POLARITY    2
#define PWM_FD_INDEX_ENABLE      3

static PeripheralIoGdbusPwm *pwm_proxy = NULL;

static int __pwm_proxy_init()
{
	GError *error = NULL;

	if (pwm_proxy != NULL) {
		_E("Pwm proxy is already created");
		g_object_ref(pwm_proxy);
		return PERIPHERAL_ERROR_NONE;
	}

	pwm_proxy = peripheral_io_gdbus_pwm_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_PWM_PATH,
		NULL,
		&error);

	if (pwm_proxy == NULL) {
		_E("Failed to create pwm proxy : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

static void __pwm_proxy_deinit()
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
	GUnixFDList *fd_list = NULL;

	ret = __pwm_proxy_init();
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	if (peripheral_io_gdbus_pwm_call_open_sync(
			pwm_proxy,
			chip,
			pin,
			NULL,
			&pwm->handle,
			&ret,
			&fd_list,
			NULL,
			&error) == FALSE) {
		_E("%s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	pwm->fd_period = g_unix_fd_list_get(fd_list, PWM_FD_INDEX_PERIOD, &error);
	if (pwm->fd_period < 0) {
		_E("Failed to get fd for pwm period : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	pwm->fd_duty_cycle = g_unix_fd_list_get(fd_list, PWM_FD_INDEX_DUTY_CYCLE, &error);
	if (pwm->fd_duty_cycle < 0) {
		_E("Failed to get fd for pwm duty cycle : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	pwm->fd_polarity = g_unix_fd_list_get(fd_list, PWM_FD_INDEX_POLARITY, &error);
	if (pwm->fd_polarity < 0) {
		_E("Failed to get fd for pwm polarity : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	pwm->fd_enable = g_unix_fd_list_get(fd_list, PWM_FD_INDEX_ENABLE, &error);
	if (pwm->fd_enable < 0) {
		_E("Failed to get fd for pwm enable : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_UNKNOWN;
	}

	g_object_unref(fd_list);

	return ret;
}

int peripheral_gdbus_pwm_close(peripheral_pwm_h pwm)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;

	if (pwm_proxy == NULL) {
		_E("Can't try to pwm close because pwm proxy is NULL.");
		return PERIPHERAL_ERROR_UNKNOWN;
	}

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

	__pwm_proxy_deinit();

	return ret;
}