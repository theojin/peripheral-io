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

#ifndef __PERIPHERAL_INTERFACE_PWM_H__
#define __PERIPHERAL_INTERFACE_PWM_H__

#include "peripheral_interface_common.h"

#define PWM_BUF_MAX 16

/**
* @brief pwm_close() deinit pwm pin.
*
* @param[in] chip pwm chip number
* @param[in] pin pwm pin number
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
void peripheral_interface_pwm_close(peripheral_pwm_h pwm);

/**
* @brief pwm_set_period() sets the pwm period.
*
* @param[in] chip pwm chip number
* @param[in] pin pwm pin number
* @param[in] period pwm period
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_pwm_set_period(peripheral_pwm_h pwm, uint32_t period);

/**
* @brief pwm_set_duty_cycle() sets the pwm duty cycle.
*
* @param[in] chip pwm chip number
* @param[in] pin pwm pin number
* @param[in] duty_cycle pwm duty cycle
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_pwm_set_duty_cycle(peripheral_pwm_h pwm, uint32_t duty_cycle);

/**
* @brief pwm_set_polarity() sets the pwm polarity.
*
* @param[in] chip pwm chip number
* @param[in] pin pwm pin number
* @param[in] polarity pwm polarity
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_pwm_set_polarity(peripheral_pwm_h pwm, peripheral_pwm_polarity_e polarity);

/**
* @brief pwm_set_enable() sets the pwm state.
*
* @param[in] chip pwm chip number
* @param[in] pin pwm pin number
* @param[in] enable pwm enable/disabled state value
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_pwm_set_enable(peripheral_pwm_h pwm, bool enable);

#endif /* __PERIPHERAL_INTERFACE_PWM_H__ */
