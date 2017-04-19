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

#define PERIPHERAL_DBUS_INTERFACE	"org.tizen.system.peripheral_io"
#define PERIPHERAL_DBUS_PATH		"/Org/Tizen/System/Peripheral_io"
#define PERIPHERAL_DBUS_NAME		"org.tizen.system.peripheral_io"

#define PERIPHERAL_METHOD_GPIO	"gpio"
#define PERIPHERAL_METHOD_I2C	"i2c"
#define PERIPHERAL_METHOD_PWM	"pwm"
#define PERIPHERAL_METHOD_SPI	"spi"
#define PERIPHERAL_METHOD_UART	"uart"

int set_dbus_connection(void);
void unset_dbus_connection(void);
GDBusConnection *get_dbus_connection(void);


int peripheral_dbus_gpio(peripheral_gpio_h gpio, char * sensorid, char *funcname, int write_value, int *read_value);
int peripheral_dbus_i2c(peripheral_i2c_h i2c, char * sensorid, char *funcname, int value, unsigned char *data, int addr);
int peripheral_dbus_pwm(peripheral_pwm_context_h dev, char * sensorid, char *funcname);

#endif /* __PERIPHERAL_DBUS_H_ */
