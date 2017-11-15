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

#define SYSFS_PWM_PATH	"/sys/class/pwm"

#define PATH_BUF_MAX	64
#define PWM_BUF_MAX	16
#define MAX_ERR_LEN	255

int peripheral_interface_pwm_close(peripheral_pwm_h pwm)
{
	int status;

	status = close(pwm->fd_period);
	CHECK_ERROR(status);

	status = close(pwm->fd_duty_cycle);
	CHECK_ERROR(status);

	status = close(pwm->fd_polarity);
	CHECK_ERROR(status);

	status = close(pwm->fd_enable);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_pwm_set_period(peripheral_pwm_h pwm, uint32_t period)
{
	int len, status;
	char pwm_buf[PWM_BUF_MAX] = {0};

	len = snprintf(pwm_buf, sizeof(pwm_buf), "%d", period);
	status = write(pwm->fd_period, pwm_buf, len);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_pwm_set_duty_cycle(peripheral_pwm_h pwm, uint32_t duty_cycle)
{
	int len, status;
	char pwm_buf[PWM_BUF_MAX] = {0};

	len = snprintf(pwm_buf, sizeof(pwm_buf), "%d", duty_cycle);
	status = write(pwm->fd_duty_cycle, pwm_buf, len);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_pwm_set_polarity(peripheral_pwm_h pwm, peripheral_pwm_polarity_e polarity)
{
	int status;

	if (polarity == PERIPHERAL_PWM_POLARITY_ACTIVE_HIGH)
		status = write(pwm->fd_polarity, "normal", strlen("normal")+1);
	else if (polarity == PERIPHERAL_PWM_POLARITY_ACTIVE_LOW)
		status = write(pwm->fd_polarity, "inversed", strlen("inversed")+1);
	else {
		_E("Invalid pwm polarity : %d", polarity);
		return -EINVAL;
	}

	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_pwm_set_enable(peripheral_pwm_h pwm, bool enable)
{
	int len, status;
	char pwm_buf[PWM_BUF_MAX] = {0};

	len = snprintf(pwm_buf, sizeof(pwm_buf), "%d", enable);
	status = write(pwm->fd_enable, pwm_buf, len);
	CHECK_ERROR(status);

	return 0;
}
