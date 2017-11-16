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

#ifndef __PERIPHERAL_GDBUS_UART_H_
#define __PERIPHERAL_GDBUS_UART_H_

#include "peripheral_gdbus_common.h"

int peripheral_gdbus_uart_open(peripheral_uart_h uart, int port);
int peripheral_gdbus_uart_close(void);

#endif /* __PERIPHERAL_GDBUS_UART_H_ */
