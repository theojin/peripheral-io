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
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>

#include "gpio.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

#define MAX_ERR_LEN 255

int gpio_set_direction(peripheral_gpio_h gpio, gpio_direction_e dir)
{
	int status;

	if (dir == GPIO_DIRECTION_IN)
		status = write(gpio->fd_direction, "in", strlen("in")+1);
	else if (dir == GPIO_DIRECTION_OUT_HIGH)
		status = write(gpio->fd_direction, "high", strlen("high")+1);
	else if (dir == GPIO_DIRECTION_OUT_LOW)
		status = write(gpio->fd_direction, "low", strlen("low")+1);
	else {
		_E("Error: gpio direction is wrong\n");
		return -EIO;
	}

	if (status <= 0) {
		_E("Error: gpio direction set error\n");
		return -EIO;
	}

	return 0;
}

int gpio_set_edge_mode(peripheral_gpio_h gpio, gpio_edge_e edge)
{
	int status;

	if (edge == GPIO_EDGE_NONE)
		status = write(gpio->fd_edge, "none", strlen("none")+1);
	else if (edge == GPIO_EDGE_RISING)
		status = write(gpio->fd_edge, "rising", strlen("rising")+1);
	else if (edge == GPIO_EDGE_FALLING)
		status = write(gpio->fd_edge, "falling", strlen("falling")+1);
	else if (edge == GPIO_EDGE_BOTH)
		status = write(gpio->fd_edge, "both", strlen("both")+1);
	else {
		_E("Error: gpio edge is wrong\n");
		return -EIO;
	}

	if (status <= 0) {
		_E("Error: gpio edge set error\n");
		return -EIO;
	}

	return 0;
}

int gpio_write(peripheral_gpio_h gpio, int value)
{
	int status;

	if (value == 1)
		status = write(gpio->fd_value, "1", strlen("1")+1);
	else if (value == 0)
		status = write(gpio->fd_value, "0", strlen("0")+1);
	else {
		_E("Error: gpio write value error \n");
		return -EIO;
	}

	if (status <= 0) {
		_E("Error: gpio write error\n");
		return -EIO;
	}

	return 0;
}

int gpio_read(peripheral_gpio_h gpio, int *value)
{
	int len;
	char gpio_buf[GPIO_BUFFER_MAX] = {0, };

	len = read(gpio->fd_value, &gpio_buf, 1);
	if (len <= 0) {
		_E("Error: gpio read error \n");
		return -EIO;
	}

	if (0 == strncmp(gpio_buf, "1", strlen("1")))
		*value = 1;
	else if (0 == strncmp(gpio_buf, "0", strlen("0")))
		*value = 0;
	else {
		_E("Error: gpio value is error \n");
		return -EIO;
	}

	return 0;
}

int gpio_close(peripheral_gpio_h gpio)
{
	int status;

	status = close(gpio->fd_direction);
	if (status < 0) {
		_E("Error: gpio direction fd close error \n");
		return -EIO;
	}

	status = close(gpio->fd_edge);
	if (status < 0) {
		_E("Error: gpio edge fd close error \n");
		return -EIO;
	}

	status = close(gpio->fd_value);
	if (status < 0) {
		_E("Error: gpio value fd close error \n");
		return -EIO;
	}

	return 0;
}

int gpio_open_isr(peripheral_gpio_h gpio)
{
	// int fd;
	// char gpio_dev[GPIO_BUFFER_MAX] = {0, };

	// snprintf(gpio_dev, sizeof(gpio_dev)-1, SYSFS_GPIO_DIR"/gpio%d/value", gpiopin);

	// _D("open isr string [%s]", gpio_dev);

	// fd = open(gpio_dev, O_RDONLY);
	// if (fd < 0) {
	// 	char errmsg[MAX_ERR_LEN];
	// 	strerror_r(errno, errmsg, MAX_ERR_LEN);
	// 	_E("Can't Open /sys/class/gpio/gpio%d pin value: %s\n", gpiopin, errmsg);
	// 	return -ENXIO;
	// }

	// return fd;

	return 0;
}

int gpio_close_isr(peripheral_gpio_h gpio)
{
// 	if (fd <= 0) return -EINVAL;

// 	close(fd);

	return 0;
}