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

#ifndef __PERIPHERAL_INTERFACE_GPIO_H__
#define __PERIPHERAL_INTERFACE_GPIO_H__

#include "peripheral_interface_common.h"

#define GPIO_BUFFER_MAX 64

void peripheral_interface_gpio_close(peripheral_gpio_h gpio);

int peripheral_interface_gpio_set_initial_edge_into_handle(peripheral_gpio_h gpio);
int peripheral_interface_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge);
int peripheral_interface_gpio_get_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e *out_edge);

int peripheral_interface_gpio_set_initial_direction_into_handle(peripheral_gpio_h gpio);
int peripheral_interface_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction);
int peripheral_interface_gpio_get_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e *out_direction);

int peripheral_interface_gpio_write(peripheral_gpio_h gpio, uint32_t value);
int peripheral_interface_gpio_read(peripheral_gpio_h gpio, uint32_t *value);

int peripheral_interface_gpio_set_interrupted_cb(peripheral_gpio_h gpio, peripheral_gpio_interrupted_cb callback, void *user_data);
int peripheral_interface_gpio_unset_interrupted_cb(peripheral_gpio_h gpio);

#endif/*__PERIPHERAL_INTERFACE_GPIO_H__*/