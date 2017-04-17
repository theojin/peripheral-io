/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
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
#include <unistd.h>
#include <assert.h>

#include "peripheral_io.h"
#include "peripheral_dbus.h"
#include "peripheral_common.h"

#define PWM_NAME	"pwm"
#define PWM_ENABLE	1
#define PWM_DISABLE	0

#ifdef __cplusplus
extern "C" {
#endif

peripheral_pwm_context_h peripheral_pwm_open(int device, int channel)
{
	peripheral_pwm_context_h dev = NULL;
	int ret = PERIPHERAL_ERROR_NONE;

	assert(device >= 0);
	assert(channel >= 0);

	/* Initialize */
	dev = (peripheral_pwm_context_h)malloc(sizeof(struct _peripheral_pwm_s));

	if (dev == NULL) {
		_E("Failed to allocate peripheral_pwm_context_h");
		return NULL;
	}

	if (!get_dbus_connection())
		set_dbus_connection();

	dev->device = device;
	dev->channel = channel;

	ret = peripheral_dbus_pwm(dev, PWM_NAME, "OPEN");

	if (ret != PERIPHERAL_ERROR_NONE) {
		free(dev);
		dev = NULL;
	}

	return dev;
}

int peripheral_pwm_close(peripheral_pwm_context_h pwm)
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = peripheral_dbus_pwm(pwm, PWM_NAME, "CLOSE");

	if (ret == PERIPHERAL_ERROR_NONE) {
		free(pwm);
		pwm = NULL;
	}

	return ret;
}


int	peripheral_pwm_set_duty_cycle(peripheral_pwm_context_h pwm, int duty_cycle)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (pwm->duty_cycle != duty_cycle) {
		int duty_value = 0;

		duty_value = pwm->duty_cycle;
		pwm->duty_cycle = duty_cycle;
		ret = peripheral_dbus_pwm(pwm, PWM_NAME, "SET_DUTY");

		if (ret != PERIPHERAL_ERROR_NONE)
			pwm->duty_cycle = duty_value;
	}

	return ret;
}

int peripheral_pwm_set_period(peripheral_pwm_context_h pwm, int period)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (pwm->period != period) {
		int period_value = 0;

		period_value = pwm->period;
		pwm->period = period;
		ret = peripheral_dbus_pwm(pwm, PWM_NAME, "SET_PERIOD");

		if (ret != PERIPHERAL_ERROR_NONE)
			pwm->period = period_value;
	}

	return ret;
}

int	peripheral_pwm_set_enabled(peripheral_pwm_context_h pwm, peripheral_pwm_state_e enable)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (pwm->enabled != enable) {
		int enable_value = 0;

		enable_value = pwm->enabled;
		pwm->enabled = enable;
		ret = peripheral_dbus_pwm(pwm, PWM_NAME, "SET_ENABLE");

		if (ret != PERIPHERAL_ERROR_NONE)
			pwm->enabled = enable_value;
	}

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_pwm_is_enabled(peripheral_pwm_context_h pwm)
{
	if (pwm->enabled == PWM_ENABLE)
		return PWM_ENABLE;
	else
		return PWM_DISABLE;

}

int peripheral_pwm_get_duty_cycle(peripheral_pwm_context_h pwm, int *duty_cycle)
{
	int duty_value = 0;
	int ret = PERIPHERAL_ERROR_NONE;

	duty_value = pwm->duty_cycle;

	ret = peripheral_dbus_pwm(pwm, PWM_NAME, "GET_DUTY");

	(*duty_cycle) = pwm->duty_cycle;
	pwm->duty_cycle = duty_value;

	return ret;
}

int peripheral_pwm_get_period(peripheral_pwm_context_h pwm, int *period)
{
	int ret = PERIPHERAL_ERROR_NONE;
	int period_value = 0;

	period_value = pwm->period;

	ret = peripheral_dbus_pwm(pwm, PWM_NAME, "GET_PERIOD");

	(*period) = pwm->period;
	pwm->period = period_value;

	return ret;
}

#ifdef __cplusplus
}
#endif
