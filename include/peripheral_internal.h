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

#ifndef __PERIPHERAL_INTERNAL_H__
#define __PERIPHERAL_INTERNAL_H__

/**
 * @brief Internal struct for gpio context
 */
struct _peripheral_gpio_s {
	int pin;
	uint handle;
};

/**
 * @brief Internal struct for i2c context
 */
struct _peripheral_i2c_s {
	uint handle;
};

/**
 * @brief Internal struct for pwm context
 */
struct _peripheral_pwm_s {
	uint handle;
};

/**
 * @brief Internal struct for uart context
 */
struct _peripheral_uart_s {
	uint handle;
};

/**
 * @brief Internal struct for spi context
 */
struct _peripheral_spi_s {
	uint handle;
};

#endif /* __PERIPHERAL_INTERNAL_H__ */
