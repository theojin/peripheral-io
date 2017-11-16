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

#include "peripheral_interface_gpio.h"

#define MAX_ERR_LEN 255

int peripheral_interface_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	static predefined_type_s types[3] = {
		{"in",   2},
		{"high", 4},
		{"low",  3}
	};

	int status = write(gpio->fd_direction, types[direction].type, types[direction].len);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	static predefined_type_s types[4] = {
		{"none",    4},
		{"rising",  6},
		{"falling", 7},
		{"both",    4}
	};

	int status = write(gpio->fd_edge, types[edge].type, types[edge].len);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_gpio_write(peripheral_gpio_h gpio, uint32_t value)
{
	static predefined_type_s types[2] = {
		{"0", 1},
		{"1", 1}
	};

	int status = write(gpio->fd_value, types[value].type, types[value].len);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_gpio_read(peripheral_gpio_h gpio, uint32_t *value)
{
	int len;
	char gpio_buf[GPIO_BUFFER_MAX] = {0, };

	len = read(gpio->fd_value, &gpio_buf, 1);
	CHECK_ERROR(len);

	if (gpio_buf[0] == '0')
		*value = 0;
	else if (gpio_buf[0] == '1')
		*value = 1;
	else
		_E("Error: gpio value is error \n");
		return -EIO;

	return 0;
}

int peripheral_interface_gpio_close(peripheral_gpio_h gpio)
{
	int status;

	status = close(gpio->fd_direction);
	CHECK_ERROR(status);

	status = close(gpio->fd_edge);
	CHECK_ERROR(status);

	status = close(gpio->fd_value);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_gpio_open_isr(peripheral_gpio_h gpio)
{
	// TODO: set interrupted callback function

	return 0;
}

int peripheral_interface_gpio_close_isr(peripheral_gpio_h gpio)
{
	// TODO: unset interrupted callback function

	return 0;
}