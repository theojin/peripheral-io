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

#ifndef __TEST_PERIPHERAL_PWM_H__
#define __TEST_PERIPHERAL_PWM_H__

int test_peripheral_io_pwm_initialize(char *model, bool feature);

int test_peripheral_io_pwm_peripheral_pwm_open_p(void);
int test_peripheral_io_pwm_peripheral_pwm_open_n1(void);
int test_peripheral_io_pwm_peripheral_pwm_open_n2(void);
int test_peripheral_io_pwm_peripheral_pwm_open_n3(void);
int test_peripheral_io_pwm_peripheral_pwm_close_p(void);
int test_peripheral_io_pwm_peripheral_pwm_close_n(void);
int test_peripheral_io_pwm_peripheral_pwm_set_period_p(void);
int test_peripheral_io_pwm_peripheral_pwm_set_period_n(void);
int test_peripheral_io_pwm_peripheral_pwm_set_duty_cycle_p(void);
int test_peripheral_io_pwm_peripheral_pwm_set_duty_cycle_n(void);
int test_peripheral_io_pwm_peripheral_pwm_set_polarity_p1(void);
int test_peripheral_io_pwm_peripheral_pwm_set_polarity_p2(void);
int test_peripheral_io_pwm_peripheral_pwm_set_polarity_n1(void);
int test_peripheral_io_pwm_peripheral_pwm_set_polarity_n2(void);
int test_peripheral_io_pwm_peripheral_pwm_set_polarity_n3(void);
int test_peripheral_io_pwm_peripheral_pwm_set_enabled_p1(void);
int test_peripheral_io_pwm_peripheral_pwm_set_enabled_p2(void);
int test_peripheral_io_pwm_peripheral_pwm_set_enabled_n(void);

#endif /* __TEST_PERIPHERAL_PWM_H__ */