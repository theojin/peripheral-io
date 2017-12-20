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

#ifndef __TEST_PERIPHERAL_GPIO_H__
#define __TEST_PERIPHERAL_GPIO_H__

int test_peripheral_io_gpio_initialize(char *model, bool feature);

int test_peripheral_io_gpio_peripheral_gpio_open_p(void);
int test_peripheral_io_gpio_peripheral_gpio_open_n1(void);
int test_peripheral_io_gpio_peripheral_gpio_open_n2(void);
int test_peripheral_io_gpio_peripheral_gpio_close_p(void);
int test_peripheral_io_gpio_peripheral_gpio_close_n(void);
int test_peripheral_io_gpio_peripheral_gpio_set_direction_p1(void);
int test_peripheral_io_gpio_peripheral_gpio_set_direction_p2(void);
int test_peripheral_io_gpio_peripheral_gpio_set_direction_p3(void);
int test_peripheral_io_gpio_peripheral_gpio_set_direction_n1(void);
int test_peripheral_io_gpio_peripheral_gpio_set_direction_n2(void);
int test_peripheral_io_gpio_peripheral_gpio_set_direction_n3(void);
int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p1(void);
int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p2(void);
int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p3(void);
int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p4(void);
int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n1(void);
int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n2(void);
int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n3(void);
int test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_p(void);
int test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_n1(void);
int test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_n2(void);
int test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_p1(void);
int test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_p2(void);
int test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_n(void);
int test_peripheral_io_gpio_peripheral_gpio_read_p(void);
int test_peripheral_io_gpio_peripheral_gpio_read_n1(void);
int test_peripheral_io_gpio_peripheral_gpio_read_n2(void);
int test_peripheral_io_gpio_peripheral_gpio_write_p(void);
int test_peripheral_io_gpio_peripheral_gpio_write_n1(void);
int test_peripheral_io_gpio_peripheral_gpio_write_n2(void);

#endif /* __TEST_PERIPHERAL_GPIO_H__ */