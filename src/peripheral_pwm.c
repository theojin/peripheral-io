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

int peripheral_pwm_open(int device, int channel, peripheral_pwm_h *pwm)
{
	peripheral_pwm_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(device < 0 || channel < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	/* Initialize */
	handle = (peripheral_pwm_h)calloc(1, sizeof(struct _peripheral_pwm_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_pwm_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	pwm_proxy_init();

	ret = peripheral_gdbus_pwm_open(handle, device, channel);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to open PWM device : %d, channel : %d", device, channel);
		free(handle);
		handle = NULL;
	}
	*pwm = handle;

	return ret;
}

int peripheral_pwm_close(peripheral_pwm_h pwm)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	if ((ret = peripheral_gdbus_pwm_close(pwm)) < 0)
		_E("Failed to close PWM device, continuing anyway, ret : %d", ret);

	pwm_proxy_deinit();
	free(pwm);

	return ret;
}

int peripheral_pwm_set_period(peripheral_pwm_h pwm, int period)
{
	int ret;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_set_period(pwm, period);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set period, ret : %d", ret);

	return ret;
}

int peripheral_pwm_get_period(peripheral_pwm_h pwm, int *period)
{
	int ret;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_get_period(pwm, period);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get period, ret : %d", ret);

	return ret;
}

int peripheral_pwm_set_duty_cycle(peripheral_pwm_h pwm, int duty_cycle)
{
	int ret;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_set_duty_cycle(pwm, duty_cycle);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set duty cycle, ret : %d", ret);

	return ret;
}

int peripheral_pwm_get_duty_cycle(peripheral_pwm_h pwm, int *duty_cycle)
{
	int ret;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_get_duty_cycle(pwm, duty_cycle);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get duty cycle, ret : %d", ret);

	return ret;
}

int peripheral_pwm_set_polarity(peripheral_pwm_h pwm, peripheral_pwm_polarity_e polarity)
{
	int ret;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");
	RETVM_IF(polarity > PERIPHERAL_PWM_POLARITY_INVERSED, PERIPHERAL_ERROR_INVALID_PARAMETER,
		"Invalid polarity parameter");

	ret = peripheral_gdbus_pwm_set_polarity(pwm, polarity);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set polarity, ret : %d", ret);

	return ret;
}

int peripheral_pwm_get_polarity(peripheral_pwm_h pwm, peripheral_pwm_polarity_e *polarity)
{
	int ret;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_get_polarity(pwm, polarity);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get polarity, ret : %d", ret);

	return ret;
}

int peripheral_pwm_set_enable(peripheral_pwm_h pwm, bool enable)
{
	int ret;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_set_enable(pwm, enable);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set enable, ret : %d", ret);

	return ret;
}

int peripheral_pwm_get_enable(peripheral_pwm_h pwm, bool *enable)
{
	int ret;

	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_get_enable(pwm, enable);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get enable, ret : %d", ret);

	return ret;
}
