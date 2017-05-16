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
#include "peripheral_gdbus_pwm.h"
#include "peripheral_common.h"

#define PWM_ENABLE	1
#define PWM_DISABLE	0

peripheral_pwm_h peripheral_pwm_open(int device, int channel)
{
	peripheral_pwm_h dev = NULL;
	int ret = PERIPHERAL_ERROR_NONE;

	assert(device >= 0);
	assert(channel >= 0);

	/* Initialize */
	dev = (peripheral_pwm_h)malloc(sizeof(struct _peripheral_pwm_s));

	if (dev == NULL) {
		_E("Failed to allocate peripheral_pwm_h");
		return NULL;
	}

	pwm_proxy_init();

	dev->device = device;
	dev->channel = channel;

	ret = peripheral_gdbus_pwm_open(dev, device, channel);

	if (ret != PERIPHERAL_ERROR_NONE) {
		free(dev);
		dev = NULL;
	}

	return dev;
}

int peripheral_pwm_close(peripheral_pwm_h pwm)
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = peripheral_gdbus_pwm_close(pwm);
	pwm_proxy_deinit();

	if (ret == PERIPHERAL_ERROR_NONE) {
		free(pwm);
		pwm = NULL;
	}

	return ret;
}


int	peripheral_pwm_set_duty_cycle(peripheral_pwm_h pwm, int duty_cycle)
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = peripheral_gdbus_pwm_set_duty_cycle(pwm, duty_cycle);

	if (ret != PERIPHERAL_ERROR_NONE)
		pwm->duty_cycle = duty_cycle;

	return ret;
}

int peripheral_pwm_set_period(peripheral_pwm_h pwm, int period)
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = peripheral_gdbus_pwm_set_period(pwm, period);

	if (ret != PERIPHERAL_ERROR_NONE)
		pwm->period = period;

	return ret;
}

int	peripheral_pwm_set_enabled(peripheral_pwm_h pwm, peripheral_pwm_state_e enable)
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = peripheral_gdbus_pwm_set_enable(pwm, enable);

	if (ret != PERIPHERAL_ERROR_NONE)
		pwm->enabled = enable;

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_pwm_is_enabled(peripheral_pwm_h pwm)
{
	if (pwm->enabled == PWM_ENABLE)
		return PWM_ENABLE;
	else
		return PWM_DISABLE;
}

int peripheral_pwm_get_duty_cycle(peripheral_pwm_h pwm, int *duty_cycle)
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = peripheral_gdbus_pwm_get_duty_cycle(pwm, duty_cycle);

	if (ret != PERIPHERAL_ERROR_NONE)
		pwm->duty_cycle = *duty_cycle;

	return ret;
}

int peripheral_pwm_get_period(peripheral_pwm_h pwm, int *period)
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = peripheral_gdbus_pwm_get_period(pwm, period);

	if (ret != PERIPHERAL_ERROR_NONE)
		pwm->period = *period;

	return ret;
}
