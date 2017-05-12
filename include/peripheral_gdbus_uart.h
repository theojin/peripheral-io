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

void uart_proxy_init(void);
void uart_proxy_deinit();

int peripheral_gdbus_uart_open(peripheral_uart_h uart, int port);
int peripheral_gdbus_uart_close(peripheral_uart_h uart);
int peripheral_gdbus_uart_flush(peripheral_uart_h uart);
int peripheral_gdbus_uart_set_baudrate(peripheral_uart_h uart, peripheral_uart_baudrate_e baud);
int peripheral_gdbus_uart_set_mode(peripheral_uart_h uart, peripheral_uart_bytesize_e bytesize, peripheral_uart_parity_e parity, peripheral_uart_stopbits_e stopbits);
int peripheral_gdbus_uart_set_flowcontrol(peripheral_uart_h uart, bool xonxoff, bool rtscts);
int peripheral_gdbus_uart_read(peripheral_uart_h uart, uint8_t *data, int length);
int peripheral_gdbus_uart_write(peripheral_uart_h uart, uint8_t *data, int length);

#endif /* __PERIPHERAL_GDBUS_UART_H_ */
