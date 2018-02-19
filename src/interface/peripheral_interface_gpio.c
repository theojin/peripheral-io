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

#include <poll.h>
#include "peripheral_interface_gpio.h"

#define GPIO_INTERRUPTED_CALLBACK_UNSET 0
#define GPIO_INTERRUPTED_CALLBACK_SET   1

int peripheral_interface_gpio_set_initial_direction_into_handle(peripheral_gpio_h gpio)
{
	static predefined_type_s types[2] = {
		{"in",   2},
		{"out",  3},
	};

	int index;
	char gpio_buf[GPIO_BUFFER_MAX] = {0, };

	int ret = read(gpio->fd_direction, &gpio_buf, GPIO_BUFFER_MAX);
	CHECK_ERROR(ret <= 0);

	for (index = 0; index < 2; index++) {
		if (!strncmp(gpio_buf, types[index].type, types[index].len)) {
			// PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_HIGH and PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW : out type
			gpio->direction = (peripheral_gpio_direction_e)index;
			return PERIPHERAL_ERROR_NONE;
		}
	}

	return PERIPHERAL_ERROR_IO_ERROR;
}

/*
 *      [edge_mode]                [direction]
 *
 *          none -----------------> in, out (O)
 *
 * rising, falling, both ---------> in (O)
 *                          \
 *                           -----> out (X)
 */
int peripheral_interface_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	RETV_IF(gpio->direction == direction, PERIPHERAL_ERROR_NONE);
	RETV_IF(gpio->edge != PERIPHERAL_GPIO_EDGE_NONE, PERIPHERAL_ERROR_IO_ERROR);

	static predefined_type_s types[3] = {
		{"in",   2},
		{"high", 4},
		{"low",  3}
	};

	int ret = write(gpio->fd_direction, types[direction].type, types[direction].len);
	CHECK_ERROR(ret != types[direction].len);

	gpio->direction = direction;

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_gpio_set_initial_edge_into_handle(peripheral_gpio_h gpio)
{
	static predefined_type_s types[4] = {
		{"none",    4},
		{"rising",  6},
		{"falling", 7},
		{"both",    4}
	};

	int index;
	char gpio_buf[GPIO_BUFFER_MAX] = {0, };

	int ret = read(gpio->fd_edge, &gpio_buf, GPIO_BUFFER_MAX);
	CHECK_ERROR(ret <= 0);

	for (index = 0; index < 4; index++) {
		if (!strncmp(gpio_buf, types[index].type, types[index].len)) {
			gpio->edge = (peripheral_gpio_edge_e)index;
			return PERIPHERAL_ERROR_NONE;
		}
	}

	return PERIPHERAL_ERROR_IO_ERROR;
}

/*
 * [direction]          [edge_mode]
 *
 *    in ---------> none, rising, falling, both (O)
 *
 *    out --------> none (O)
 *          \
 *           -----> rising, falling, both (X)
 */
int peripheral_interface_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	RETV_IF(gpio->edge == edge, PERIPHERAL_ERROR_NONE);
	RETV_IF(gpio->direction != PERIPHERAL_GPIO_DIRECTION_IN, PERIPHERAL_ERROR_IO_ERROR);

	static predefined_type_s types[4] = {
		{"none",    4},
		{"rising",  6},
		{"falling", 7},
		{"both",    4}
	};

	int ret = write(gpio->fd_edge, types[edge].type, types[edge].len);
	CHECK_ERROR(ret != types[edge].len);

	gpio->edge = edge;

	return PERIPHERAL_ERROR_NONE;
}

/*
 * [direction]     [value]
 *
 *    in ---------> write (X)
 *    out --------> write (O)
 */
int peripheral_interface_gpio_write(peripheral_gpio_h gpio, uint32_t value)
{
	RETV_IF(gpio->direction == PERIPHERAL_GPIO_DIRECTION_IN, PERIPHERAL_ERROR_IO_ERROR);

	static predefined_type_s types[2] = {
		{"0", 1},
		{"1", 1}
	};

	int ret = write(gpio->fd_value, types[value].type, types[value].len);
	CHECK_ERROR(ret != types[value].len);

	return PERIPHERAL_ERROR_NONE;
}

/*
 * [direction]     [value]
 *
 *    in ---------> read (O)
 *    out --------> read (O)
 */
int peripheral_interface_gpio_read(peripheral_gpio_h gpio, uint32_t *value)
{
	int ret;
	int length = 1;
	char gpio_buf[GPIO_BUFFER_MAX] = {0, };

	lseek(gpio->fd_value, 0, SEEK_SET);
	ret = read(gpio->fd_value, &gpio_buf, length);
	CHECK_ERROR(ret != length);

	if (gpio_buf[0] == '0') {
		*value = 0;
	} else if (gpio_buf[0] == '1') {
		*value = 1;
	} else {
		_E("Error: gpio value is error \n");
		return PERIPHERAL_ERROR_IO_ERROR;
	}

	return PERIPHERAL_ERROR_NONE;
}

void peripheral_interface_gpio_close(peripheral_gpio_h gpio)
{
	peripheral_interface_gpio_unset_interrupted_cb(gpio);

	close(gpio->fd_direction);
	close(gpio->fd_edge);
	close(gpio->fd_value);
}

static gboolean __peripheral_interface_gpio_interrupted_cb_invoke(gpointer data)
{
	peripheral_gpio_h gpio = (peripheral_gpio_h)data;
	gpio->cb_info.cb(gpio, gpio->cb_info.error, gpio->cb_info.user_data);
	return FALSE;
}

static gpointer __peripheral_interface_gpio_poll(void *data)
{
	peripheral_gpio_h gpio = (peripheral_gpio_h)data;

	int ret;
	int poll_state = 0;
	struct pollfd poll_fd;

	poll_fd.fd = gpio->fd_value;
	poll_fd.events = POLLPRI;

	uint32_t value;

	while (g_atomic_int_get(&gpio->cb_info.status) == GPIO_INTERRUPTED_CALLBACK_SET) {

		poll_state = poll(&poll_fd, 1, 3000);

		if (poll_state == 0)
			continue;

		if (poll_state < 0) {
			_E("poll failed!");
			gpio->cb_info.error = PERIPHERAL_ERROR_IO_ERROR;
			g_idle_add_full(G_PRIORITY_HIGH_IDLE, __peripheral_interface_gpio_interrupted_cb_invoke, gpio, NULL);
			break;
		}

		if (poll_fd.revents & POLLPRI) {
			ret = peripheral_interface_gpio_read(gpio, &value);
			if (ret != PERIPHERAL_ERROR_NONE)
				continue;
		} else {
			continue;
		}

		if (gpio->edge == PERIPHERAL_GPIO_EDGE_NONE)
			continue;

		if (gpio->edge == PERIPHERAL_GPIO_EDGE_RISING && value == 0)
			continue;

		if (gpio->edge == PERIPHERAL_GPIO_EDGE_FALLING && value == 1)
			continue;

		gpio->cb_info.error = PERIPHERAL_ERROR_NONE;
		g_idle_add_full(G_PRIORITY_HIGH_IDLE, __peripheral_interface_gpio_interrupted_cb_invoke, gpio, NULL);
	}

	return NULL;
}

int peripheral_interface_gpio_set_interrupted_cb(peripheral_gpio_h gpio, peripheral_gpio_interrupted_cb callback, void *user_data)
{
	RETV_IF(gpio->direction != PERIPHERAL_GPIO_DIRECTION_IN, PERIPHERAL_ERROR_IO_ERROR);

	peripheral_interface_gpio_unset_interrupted_cb(gpio);

	gpio->cb_info.cb = callback;
	gpio->cb_info.user_data = user_data;
	g_atomic_int_set(&gpio->cb_info.status, GPIO_INTERRUPTED_CALLBACK_SET);
	gpio->cb_info.thread = g_thread_new(NULL, __peripheral_interface_gpio_poll, gpio);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_gpio_unset_interrupted_cb(peripheral_gpio_h gpio)
{
	g_atomic_int_set(&gpio->cb_info.status, GPIO_INTERRUPTED_CALLBACK_UNSET);

	if (gpio->cb_info.thread != NULL) {
		g_thread_join(gpio->cb_info.thread);
		gpio->cb_info.thread = NULL;
	}

	return PERIPHERAL_ERROR_NONE;
}
