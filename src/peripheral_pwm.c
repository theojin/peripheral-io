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
#include "peripheral_internal.h"

#define PWM_ENABLE	1
#define PWM_DISABLE	0

int peripheral_pwm_open(int device, int channel, peripheral_pwm_h* pwm)
{
	peripheral_pwm_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	assert(device >= 0);
	assert(channel >= 0);

	/* Initialize */
	handle = (peripheral_pwm_h)calloc(1, sizeof(struct _peripheral_pwm_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_pwm_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	pwm_proxy_init();

	ret = peripheral_gdbus_pwm_open(handle, device, channel);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("PWM open error (%d, %d)", device, channel);
		free(handle);
		handle = NULL;
	}
	*pwm = handle;

	return ret;
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

int peripheral_pwm_set_period(peripheral_pwm_h pwm, int period)
{
	if (pwm == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_pwm_set_period(pwm, period);
}

int peripheral_pwm_get_period(peripheral_pwm_h pwm, int *period)
{
	if (pwm == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_pwm_get_period(pwm, period);
}

int peripheral_pwm_set_duty_cycle(peripheral_pwm_h pwm, int duty_cycle)
{
	if (pwm == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_pwm_set_duty_cycle(pwm, duty_cycle);
}

int peripheral_pwm_get_duty_cycle(peripheral_pwm_h pwm, int *duty_cycle)
{
	if (pwm == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_pwm_get_duty_cycle(pwm, duty_cycle);
}

int peripheral_pwm_set_enable(peripheral_pwm_h pwm, peripheral_pwm_state_e enable)
{
	if (pwm == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_pwm_set_enable(pwm, enable);
}

int peripheral_pwm_get_enable(peripheral_pwm_h pwm, peripheral_pwm_state_e *enable)
{
	if (pwm == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_pwm_get_enable(pwm, enable);
}
