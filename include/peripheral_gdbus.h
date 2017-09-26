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
#ifndef __PERIPHERAL_GDBUS_H__
#define __PERIPHERAL_GDBUS_H__

#include <gio/gio.h>

#define PERIPHERAL_GDBUS_INTERFACE	"org.tizen.peripheral_io"
#define PERIPHERAL_GDBUS_GPIO_PATH	"/Org/Tizen/Peripheral_io/Gpio"
#define PERIPHERAL_GDBUS_I2C_PATH	"/Org/Tizen/Peripheral_io/I2c"
#define PERIPHERAL_GDBUS_PWM_PATH	"/Org/Tizen/Peripheral_io/Pwm"
#define PERIPHERAL_GDBUS_UART_PATH	"/Org/Tizen/Peripheral_io/Uart"
#define PERIPHERAL_GDBUS_SPI_PATH	"/Org/Tizen/Peripheral_io/Spi"
#define PERIPHERAL_GDBUS_NAME		"org.tizen.peripheral_io"

#endif /* __PERIPHERAL_GDBUS_H__ */
