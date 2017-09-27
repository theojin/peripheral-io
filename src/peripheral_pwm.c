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
#include <system_info.h>

#include "peripheral_io.h"
#include "peripheral_gdbus_pwm.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

#define PERIPHERAL_IO_PWM_FEATURE "http://tizen.org/feature/peripheral_io.pwm"

#define PWM_FEATURE_UNKNOWN -1
#define PWM_FEATURE_FALSE    0
#define PWM_FEATURE_TRUE     1

static int pwm_feature = PWM_FEATURE_UNKNOWN;

static bool __is_feature_supported()
{
	bool feature = false;

	if (pwm_feature == PWM_FEATURE_UNKNOWN) {
		system_info_get_platform_bool(PERIPHERAL_IO_PWM_FEATURE, &feature);
		pwm_feature = (feature ? PWM_FEATURE_TRUE : PWM_FEATURE_FALSE);
	}

	return (pwm_feature == PWM_FEATURE_TRUE ? true : false);
}


int peripheral_pwm_open(int chip, int pin, peripheral_pwm_h *pwm)
{
	peripheral_pwm_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "PWM feature is not supported");
	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid pwm handle");
	RETVM_IF(chip < 0 || pin < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	/* Initialize */
	handle = (peripheral_pwm_h)calloc(1, sizeof(struct _peripheral_pwm_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_pwm_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	pwm_proxy_init();

	ret = peripheral_gdbus_pwm_open(handle, chip, pin);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to open PWM chip : %d, pin : %d", chip, pin);
		free(handle);
		handle = NULL;
	}
	*pwm = handle;

	return ret;
}

int peripheral_pwm_close(peripheral_pwm_h pwm)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "PWM feature is not supported");
	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	if ((ret = peripheral_gdbus_pwm_close(pwm)) < 0)
		_E("Failed to close PWM chip, continuing anyway, ret : %d", ret);

	pwm_proxy_deinit();
	free(pwm);

	return ret;
}

int peripheral_pwm_set_period(peripheral_pwm_h pwm, uint32_t period_ns)
{
	int ret;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "PWM feature is not supported");
	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_set_period(pwm, (int)period_ns);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set period, ret : %d", ret);

	return ret;
}

int peripheral_pwm_set_duty_cycle(peripheral_pwm_h pwm, uint32_t duty_cycle_ns)
{
	int ret;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "PWM feature is not supported");
	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_set_duty_cycle(pwm, (int)duty_cycle_ns);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set duty cycle, ret : %d", ret);

	return ret;
}

int peripheral_pwm_set_polarity(peripheral_pwm_h pwm, peripheral_pwm_polarity_e polarity)
{
	int ret;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "PWM feature is not supported");
	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");
	RETVM_IF((polarity < PERIPHERAL_PWM_POLARITY_ACTIVE_HIGH) || (polarity > PERIPHERAL_PWM_POLARITY_ACTIVE_LOW), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid polarity parameter");

	ret = peripheral_gdbus_pwm_set_polarity(pwm, polarity);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set polarity, ret : %d", ret);

	return ret;
}

int peripheral_pwm_set_enabled(peripheral_pwm_h pwm, bool enable)
{
	int ret;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "PWM feature is not supported");
	RETVM_IF(pwm == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "pwm handle is NULL");

	ret = peripheral_gdbus_pwm_set_enable(pwm, enable);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set enable, ret : %d", ret);

	return ret;
}
