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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "peripheral_io.h"
#include "peripheral_gdbus_uart.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

/**
 * @brief Initializes uart communication and creates uart handle.
 */
int peripheral_uart_open(int port, peripheral_uart_h *uart)
{
	peripheral_uart_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	if (port < 0)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	handle = (peripheral_uart_h)calloc(1, sizeof(struct _peripheral_uart_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_uart_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	uart_proxy_init();

	ret = peripheral_gdbus_uart_open(handle, port);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("[PERIPHERAL] UART open error\n");
		free(handle);
		handle = NULL;
	}
	*uart = handle;

	return ret;
}

/**
 * @brief Destory the uart handle and release the communication.
 */
int peripheral_uart_close(peripheral_uart_h uart)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (uart == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_gdbus_uart_close(uart);
	uart_proxy_deinit();

	free(uart);
	uart = NULL;

	return ret;
}

/**
 * @brief Flush all input that has received but not yet been read by the uart
 *        device, or all output written but not transmitted to the uart device.
 */
int peripheral_uart_flush(peripheral_uart_h uart)
{
	if (uart == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_uart_flush(uart);
}

/**
 * @brief Sets baudrate of the uart device.
 */
int peripheral_uart_set_baudrate(peripheral_uart_h uart, peripheral_uart_baudrate_e baud)
{
	if (uart == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_uart_set_baudrate(uart, baud);
}

/**
 * @brief Sets baudrate of the uart device.
 */
int peripheral_uart_set_mode(peripheral_uart_h uart, peripheral_uart_bytesize_e bytesize, peripheral_uart_parity_e parity, peripheral_uart_stopbits_e stopbits)
{
	if (uart == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_uart_set_mode(uart, bytesize, parity, stopbits);
}

/**
 * @brief Sets baudrate of the uart device.
 */
int peripheral_uart_set_flowcontrol(peripheral_uart_h uart, bool xonxoff, bool rtscts)
{
	if (uart == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_uart_set_flowcontrol(uart, xonxoff, rtscts);
}

/**
 * @brief Reads data from the uart device.
 */
int peripheral_uart_read(peripheral_uart_h uart, uint8_t *data, int length)
{
	if (uart == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_uart_read(uart, data, length);
}

/**
 * @brief Write data to the uart device.
 */
int peripheral_uart_write(peripheral_uart_h uart, uint8_t *data, int length)
{
	if (uart == NULL) return PERIPHERAL_ERROR_INVALID_PARAMETER;

	return peripheral_gdbus_uart_write(uart, data, length);
}
