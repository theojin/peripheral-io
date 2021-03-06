/*
 * Copyright (c) 2017-2018 Samsung Electronics Co., Ltd.
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

#ifndef __PERIPHERAL_HANDLE_H__
#define __PERIPHERAL_HANDLE_H__

#include <gio/gio.h>

typedef struct _peripheral_gpio_interrupted_cb_info_s {
	GThread *thread;
	peripheral_gpio_interrupted_cb cb;
	peripheral_error_e error;
	void *user_data;
	gint status;
} interrupted_cb_info_s;

/**
 * @brief Internal struct for gpio context
 */
struct _peripheral_gpio_s {
	uint handle;
	int fd_direction;
	int fd_edge;
	int fd_value;
	peripheral_gpio_direction_e direction;
	peripheral_gpio_edge_e edge;
	interrupted_cb_info_s cb_info;
};

/**
 * @brief Internal struct for i2c context
 */
struct _peripheral_i2c_s {
	uint handle;
	int fd;
};

/**
 * @brief Internal struct for pwm context
 */
struct _peripheral_pwm_s {
	uint handle;
	int fd_period;
	int fd_duty_cycle;
	int fd_polarity;
	int fd_enable;
};

/**
 * @brief Internal struct for adc context
 */
struct _peripheral_adc_s {
	uint handle;
	int fd;
};

/**
 * @brief Internal struct for uart context
 */
struct _peripheral_uart_s {
	uint handle;
	int fd;
};

/**
 * @brief Internal struct for spi context
 */
struct _peripheral_spi_s {
	uint handle;
	int fd;
};

#endif /* __PERIPHERAL_HANDLE_H__ */
