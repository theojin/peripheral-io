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

#ifndef __PERIPHERAL_INTERFACE_UART_H__
#define __PERIPHERAL_INTERFACE_UART_H__

#include "peripheral_interface_common.h"

/**
* @brief uart_close() closes uart port.
*
* @param[in] file_hndl handle of uart_context
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
void peripheral_interface_uart_close(peripheral_uart_h uart);

/**
* @brief uart_flush() flushes uart buffer.
*
* @param[in] file_hndl handle of uart_context
*/
void peripheral_interface_uart_flush(peripheral_uart_h uart);

/**
* @brief uart_set_baudrate() sets uart baud rate.
*
* @param[in] file_hndl handle of uart_context
* @param[in] baud uart baud rate
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_uart_set_baud_rate(peripheral_uart_h uart, peripheral_uart_baud_rate_e baud);

/**
* @brief peripheral_bus_uart_set_byte_size() set byte size.
*
* @param[in] file_hndl handle of uart_context
* @param[in] byte_size uart byte size
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_uart_set_byte_size(peripheral_uart_h uart, peripheral_uart_byte_size_e byte_size);

/**
* @brief peripheral_bus_uart_set_parity() set parity bit.
*
* @param[in] file_hndl handle of uart_context
* @param[in] parity uart parity type (even/odd/none)
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_uart_set_parity(peripheral_uart_h uart, peripheral_uart_parity_e parity);

/**
* @brief peripheral_bus_uart_set_stop_bits() set stop bits.
*
* @param[in] file_hndl handle of uart_context
* @param[in] stop_bits uart stop bits
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_uart_set_stop_bits(peripheral_uart_h uart, peripheral_uart_stop_bits_e stop_bits);

/**
* @brief uart_set_flow_control() set flow control settings.
*
* @param[in] file_hndl handle of uart_context
* @param[in] xonxoff ixon/ixoff
* @param[in] rtscts rts/cts
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_uart_set_flow_control(peripheral_uart_h uart, peripheral_uart_software_flow_control_e xonxoff, peripheral_uart_hardware_flow_control_e rtscts);

/**
* @brief uart_read() reads data over uart bus.
*
* @param[in] file_hndl handle of uart_context
* @param[in] buf the pointer of data buffer
* @param[in] length size to read
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_uart_read(peripheral_uart_h uart, uint8_t *buf, uint32_t length);

/**
* @brief uart_write() writes data over uart bus.
*
* @param[in] file_hndl handle of uart_context
* @param[in] buf the pointer of data buffer
* @param[in] length size to write
* @return On success, 0 is returned. On failure, a negative value is returned.
*/
int peripheral_interface_uart_write(peripheral_uart_h uart, uint8_t *buf, uint32_t length);

#endif /* __PERIPHERAL_INTERFACE_UART_H__ */

