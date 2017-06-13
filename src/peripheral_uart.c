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
	int ret;

	RETVM_IF(port < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid port number");

	handle = (peripheral_uart_h)calloc(1, sizeof(struct _peripheral_uart_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_uart_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	uart_proxy_init();

	ret = peripheral_gdbus_uart_open(handle, port);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to open uart port, ret : %d", ret);
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
	int ret;

	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");

	ret = peripheral_gdbus_uart_close(uart);
	if (ret < PERIPHERAL_ERROR_NONE)
		_E("Failed to close uart communication, continuing anyway, ret : %d", ret);
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
	int ret;

	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");

	ret = peripheral_gdbus_uart_flush(uart);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to flush, ret : %d", ret);

	return ret;
}

/**
 * @brief Sets baudrate of the uart device.
 */
int peripheral_uart_set_baudrate(peripheral_uart_h uart, peripheral_uart_baudrate_e baud)
{
	int ret;

	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF(baud > PERIPHERAL_UART_BAUDRATE_230400, PERIPHERAL_ERROR_INVALID_PARAMETER,
		"Invalid baud input");

	ret = peripheral_gdbus_uart_set_baudrate(uart, baud);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set baudrate, ret : %d", ret);

	return ret;
}

/**
 * @brief Sets baudrate of the uart device.
 */
int peripheral_uart_set_mode(peripheral_uart_h uart, peripheral_uart_bytesize_e bytesize, peripheral_uart_parity_e parity, peripheral_uart_stopbits_e stopbits)
{
	int ret;

	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF(bytesize > PERIPHERAL_UART_BYTESIZE_8BIT
			|| parity > PERIPHERAL_UART_PARITY_ODD
			|| stopbits > PERIPHERAL_UART_STOPBITS_2BIT,
		PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	ret = peripheral_gdbus_uart_set_mode(uart, bytesize, parity, stopbits);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set uart mode, ret : %d", ret);

	return ret;
}

/**
 * @brief Sets baudrate of the uart device.
 */
int peripheral_uart_set_flowcontrol(peripheral_uart_h uart, bool xonxoff, bool rtscts)
{
	int ret;

	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");

	ret = peripheral_gdbus_uart_set_flowcontrol(uart, xonxoff, rtscts);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set flocontrol, ret : %d", ret);

	return ret;
}

/**
 * @brief Reads data from the uart device.
 */
int peripheral_uart_read(peripheral_uart_h uart, uint8_t *data, int length)
{
	int ret;

	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF(data == NULL || length < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	ret = peripheral_gdbus_uart_read(uart, data, length);
	if (ret < PERIPHERAL_ERROR_NONE)
		_E("Failed to read from uart device, ret : %d", ret);

	return ret;
}

/**
 * @brief Write data to the uart device.
 */
int peripheral_uart_write(peripheral_uart_h uart, uint8_t *data, int length)
{
	int ret;

	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF(data == NULL || length < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	ret = peripheral_gdbus_uart_write(uart, data, length);
	if (ret < PERIPHERAL_ERROR_NONE)
		_E("Failed to write to uart device, ret : %d", ret);

	return ret;
}
