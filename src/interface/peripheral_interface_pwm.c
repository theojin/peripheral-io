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
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "peripheral_interface_pwm.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

#define SYSFS_PWM_PATH	"/sys/class/pwm"

#define PATH_BUF_MAX	64
#define PWM_BUF_MAX	16
#define MAX_ERR_LEN	255

int peripheral_interface_pwm_close(peripheral_pwm_h pwm)
{
	int status;

	status = close(pwm->fd_period);
	if (status < 0) {
		_E("Error: pwm period fd close error \n");
		return -EIO;
	}

	status = close(pwm->fd_duty_cycle);
	if (status < 0) {
		_E("Error: pwm duty cycle fd close error \n");
		return -EIO;
	}

	status = close(pwm->fd_polarity);
	if (status < 0) {
		_E("Error: pwm polarity fd close error \n");
		return -EIO;
	}

	status = close(pwm->fd_enable);
	if (status < 0) {
		_E("Error: pwm enable fd close error \n");
		return -EIO;
	}

	return 0;
}

int peripheral_interface_pwm_set_period(peripheral_pwm_h pwm, int period)
{
	int len, status;
	char pwm_buf[PWM_BUF_MAX] = {0};

	len = snprintf(pwm_buf, sizeof(pwm_buf), "%d", period);
	status = write(pwm->fd_period, pwm_buf, len);
	if (status < 0) {
		_E("Failed to set period");
		return -EIO;
	}

	return 0;
}

int peripheral_interface_pwm_set_duty_cycle(peripheral_pwm_h pwm, int duty_cycle)
{
	int len, status;
	char pwm_buf[PWM_BUF_MAX] = {0};

	len = snprintf(pwm_buf, sizeof(pwm_buf), "%d", duty_cycle);
	status = write(pwm->fd_duty_cycle, pwm_buf, len);
	if (status < 0) {
		_E("Failed to set duty cycle");
		return -EIO;
	}

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

	if (status <= 0) {
		_E("Failed to set polarity");
		return -EIO;
	}

	return 0;
}

int peripheral_interface_pwm_set_enable(peripheral_pwm_h pwm, bool enable)
{
	int len, status;
	char pwm_buf[PWM_BUF_MAX] = {0};

	len = snprintf(pwm_buf, sizeof(pwm_buf), "%d", enable);
	status = write(pwm->fd_enable, pwm_buf, len);
	if (status < 0) {
		_E("Failed to set enable");
		return -EIO;
	}

	return 0;
}
