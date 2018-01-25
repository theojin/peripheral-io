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

#include "peripheral_interface_pwm.h"

void peripheral_interface_pwm_close(peripheral_pwm_h pwm)
{
	close(pwm->fd_period);
	close(pwm->fd_duty_cycle);
	close(pwm->fd_polarity);
	close(pwm->fd_enable);
}

int peripheral_interface_pwm_set_period(peripheral_pwm_h pwm, uint32_t period)
{
	int ret;
	int length;
	char pwm_buf[PWM_BUF_MAX] = {0};

	length = snprintf(pwm_buf, sizeof(pwm_buf), "%d", period);
	ret = write(pwm->fd_period, pwm_buf, length);
	CHECK_ERROR(ret != length);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_pwm_get_period(peripheral_pwm_h pwm, uint32_t *out_period)
{
	int ret;
	char pwm_buf[PWM_BUF_MAX] = {0, };

	lseek(pwm->fd_period, 0, SEEK_SET);
	ret = read(pwm->fd_period, &pwm_buf, PWM_BUF_MAX);
	CHECK_ERROR(ret < 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_pwm_set_duty_cycle(peripheral_pwm_h pwm, uint32_t duty_cycle)
{
	int ret;
	int length;
	char pwm_buf[PWM_BUF_MAX] = {0};

	length = snprintf(pwm_buf, sizeof(pwm_buf), "%d", duty_cycle);
	ret = write(pwm->fd_duty_cycle, pwm_buf, length);
	CHECK_ERROR(ret != length);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_pwm_get_duty_cycle(peripheral_pwm_h pwm, uint32_t *out_duty_cycle)
{
	int ret;
	char pwm_buf[PWM_BUF_MAX] = {0, };

	lseek(pwm->fd_duty_cycle, 0, SEEK_SET);
	ret = read(pwm->fd_duty_cycle, &pwm_buf, PWM_BUF_MAX);
	CHECK_ERROR(ret < 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_pwm_set_polarity(peripheral_pwm_h pwm, peripheral_pwm_polarity_e polarity)
{
	static predefined_type_s types[2] = {
		{"normal",   6},
		{"inversed", 8}
	};

	int ret = write(pwm->fd_polarity, types[polarity].type, types[polarity].len);
	CHECK_ERROR(ret != types[polarity].len);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_pwm_get_polarity(peripheral_pwm_h pwm, peripheral_pwm_polarity_e *out_polarity)
{
	int ret;
	char pwm_buf[PWM_BUF_MAX] = {0, };

	lseek(pwm->fd_polarity, 0, SEEK_SET);
	ret = read(pwm->fd_polarity, &pwm_buf, PWM_BUF_MAX);
	CHECK_ERROR(ret < 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_pwm_set_enable(peripheral_pwm_h pwm, bool enable)
{
	static predefined_type_s types[2] = {
		{"0", 1},
		{"1", 1}
	};

	int ret = write(pwm->fd_enable, types[enable].type, types[enable].len);
	CHECK_ERROR(ret != types[enable].len);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_pwm_get_enable(peripheral_pwm_h pwm, bool *out_enable)
{
	int ret;
	char pwm_buf[PWM_BUF_MAX] = {0, };

	lseek(pwm->fd_enable, 0, SEEK_SET);
	ret = read(pwm->fd_enable, &pwm_buf, PWM_BUF_MAX);
	CHECK_ERROR(ret < 0);

	return PERIPHERAL_ERROR_NONE;
}
