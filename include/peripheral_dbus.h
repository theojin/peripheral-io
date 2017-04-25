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
#ifndef __PERIPHERAL_DBUS_H_
#define __PERIPHERAL_DBUS_H_

#include <gio/gio.h>

#define PERIPHERAL_DBUS_INTERFACE	"org.tizen.peripheral_io"
#define PERIPHERAL_DBUS_PATH		"/Org/Tizen/Peripheral_io"
#define PERIPHERAL_DBUS_GPIO_PATH	"/Org/Tizen/Peripheral_io/Gpio"
#define PERIPHERAL_DBUS_I2C_PATH	"/Org/Tizen/Peripheral_io/I2c"
#define PERIPHERAL_DBUS_PWM_PATH	"/Org/Tizen/Peripheral_io/Pwm"
#define PERIPHERAL_DBUS_NAME		"org.tizen.peripheral_io"

#define PERIPHERAL_METHOD_GPIO	"gpio"
#define PERIPHERAL_METHOD_I2C	"i2c"
#define PERIPHERAL_METHOD_PWM	"pwm"
#define PERIPHERAL_METHOD_SPI	"spi"
#define PERIPHERAL_METHOD_UART	"uart"

void gpio_proxy_init(void);
void i2c_proxy_init(void);
void pwm_proxy_init(void);

void gpio_proxy_deinit();
void i2c_proxy_deinit();
void pwm_proxy_deinit();

int peripheral_dbus_gpio_open(peripheral_gpio_h gpio);
int peripheral_dbus_gpio_close(peripheral_gpio_h gpio);
int peripheral_dbus_gpio_get_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e *direction);
int peripheral_dbus_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction);
int peripheral_dbus_gpio_read(peripheral_gpio_h gpio, int *value);
int peripheral_dbus_gpio_write(peripheral_gpio_h gpio, int value);
int peripheral_dbus_gpio_get_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e *edge);
int peripheral_dbus_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge);

int peripheral_dbus_i2c_open(peripheral_i2c_h i2c, int bus, int address);
int peripheral_dbus_i2c_close(peripheral_i2c_h i2c);
int peripheral_dbus_i2c_read(peripheral_i2c_h i2c, uint8_t *data, int length);
int peripheral_dbus_i2c_write(peripheral_i2c_h i2c, uint8_t *data, int length);

int peripheral_dbus_pwm_open(peripheral_pwm_context_h dev, int device, int channel);
int peripheral_dbus_pwm_close(peripheral_pwm_context_h dev);
int peripheral_dbus_pwm_get_duty_cycle(peripheral_pwm_context_h dev, int *duty_cycle);
int peripheral_dbus_pwm_set_duty_cycle(peripheral_pwm_context_h dev, int duty_cycle);
int peripheral_dbus_pwm_get_period(peripheral_pwm_context_h dev, int *period);
int peripheral_dbus_pwm_set_period(peripheral_pwm_context_h dev, int period);
int peripheral_dbus_pwm_set_enable(peripheral_pwm_context_h dev, peripheral_pwm_state_e enable);

#endif /* __PERIPHERAL_DBUS_H_ */
