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
#include <string.h>
#include <peripheral_io.h>
#include "test_peripheral_pwm.h"

#define PWM_CHIP 0
#define PWM_CHIP_INVALID -99
#define PWM_PIN 2
#define PWM_PIN_INVALID -99
#define PWM_PERIOD 1000
#define PWM_DUTY_CYCLE 100

static bool g_feature = true;
static int chip;
static int pin;

int test_peripheral_io_pwm_initialize(char *model, bool feature)
{
	g_feature = feature;

	if ((!strcmp(model, "rpi3")) || (!strcmp(model, "artik"))) {
		chip = PWM_CHIP;
		pin = PWM_PIN;
#if defined(SDTA7D)
	} else if (!strcmp(model, "sdta7d")) {
		chip = PWM_CHIP;
		pin = PWM_PIN;
#endif
	} else {
		return PERIPHERAL_ERROR_NO_DEVICE;
	}
	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_open_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_open_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_open(PWM_CHIP_INVALID, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(PWM_CHIP_INVALID, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_open_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_open(chip, PWM_PIN_INVALID, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, PWM_PIN_INVALID, &pwm_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_open_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_pwm_open(chip, pin, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_close_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_close_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_pwm_close(NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_close(NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_period_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_set_period(pwm_h, PWM_PERIOD);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_set_period(pwm_h, PWM_PERIOD);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_pwm_close(pwm_h);
			return ret;
		}

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_period_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_pwm_set_period(NULL, PWM_PERIOD);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_set_period(NULL, PWM_PERIOD);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_duty_cycle_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_set_duty_cycle(pwm_h, PWM_DUTY_CYCLE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_set_duty_cycle(pwm_h, PWM_DUTY_CYCLE);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_pwm_close(pwm_h);
			return ret;
		}

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_duty_cycle_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_pwm_set_duty_cycle(NULL, PWM_DUTY_CYCLE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_set_duty_cycle(NULL, PWM_DUTY_CYCLE);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_polarity_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_set_polarity(pwm_h, PERIPHERAL_PWM_POLARITY_ACTIVE_HIGH);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_set_polarity(pwm_h, PERIPHERAL_PWM_POLARITY_ACTIVE_HIGH);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_pwm_close(pwm_h);
			return ret;
		}

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_polarity_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_set_polarity(pwm_h, PERIPHERAL_PWM_POLARITY_ACTIVE_LOW);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_set_polarity(pwm_h, PERIPHERAL_PWM_POLARITY_ACTIVE_LOW);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_pwm_close(pwm_h);
			return ret;
		}

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_polarity_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_pwm_set_polarity(NULL, PERIPHERAL_PWM_POLARITY_ACTIVE_HIGH);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_set_polarity(NULL, PERIPHERAL_PWM_POLARITY_ACTIVE_HIGH);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_polarity_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_set_polarity(pwm_h, PERIPHERAL_PWM_POLARITY_ACTIVE_HIGH - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_set_polarity(pwm_h, PERIPHERAL_PWM_POLARITY_ACTIVE_HIGH - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_pwm_close(pwm_h);
			return ret;
		}

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_polarity_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	if (g_feature == false) {
		ret = peripheral_pwm_set_polarity(pwm_h, PERIPHERAL_PWM_POLARITY_ACTIVE_LOW + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_set_polarity(pwm_h, PERIPHERAL_PWM_POLARITY_ACTIVE_LOW + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_pwm_close(pwm_h);
			return ret;
		}

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_enabled_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	bool enable = true;

	if (g_feature == false) {
		ret = peripheral_pwm_set_enabled(pwm_h, enable);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_set_enabled(pwm_h, enable);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_pwm_close(pwm_h);
			return ret;
		}

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_enabled_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_pwm_h pwm_h = NULL;

	bool enable = false;

	if (g_feature == false) {
		ret = peripheral_pwm_set_enabled(pwm_h, enable);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_open(chip, pin, &pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_pwm_set_enabled(pwm_h, enable);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_pwm_close(pwm_h);
			return ret;
		}

		ret = peripheral_pwm_close(pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_pwm_peripheral_pwm_set_enabled_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	bool enable = true;

	if (g_feature == false) {
		ret = peripheral_pwm_set_enabled(NULL, enable);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_pwm_set_enabled(NULL, enable);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}
