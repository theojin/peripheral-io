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

#include <stdlib.h>
#include <system_info.h>

#include "peripheral_io.h"
#include "peripheral_handle.h"
#include "peripheral_gdbus_uart.h"
#include "peripheral_interface_uart.h"
#include "peripheral_log.h"

#define PERIPHERAL_IO_UART_FEATURE "http://tizen.org/feature/peripheral_io.uart"

#define UART_FEATURE_UNKNOWN -1
#define UART_FEATURE_FALSE    0
#define UART_FEATURE_TRUE     1

static int uart_feature = UART_FEATURE_UNKNOWN;

static bool __is_feature_supported(void)
{
	int ret = SYSTEM_INFO_ERROR_NONE;
	bool feature = false;

	if (uart_feature == UART_FEATURE_UNKNOWN) {
		ret = system_info_get_platform_bool(PERIPHERAL_IO_UART_FEATURE, &feature);
		RETVM_IF(ret != SYSTEM_INFO_ERROR_NONE, false, "Failed to get system info");

		uart_feature = (feature ? UART_FEATURE_TRUE : UART_FEATURE_FALSE);
	}

	return (uart_feature == UART_FEATURE_TRUE ? true : false);
}

/**
 * @brief Initializes uart communication and creates uart handle.
 */
int peripheral_uart_open(int port, peripheral_uart_h *uart)
{
	peripheral_uart_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid uart handle");
	RETVM_IF(port < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid port number");

	handle = (peripheral_uart_h)calloc(1, sizeof(struct _peripheral_uart_s));
	if (handle == NULL) {
		_E("Failed to allocate peripheral_uart_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	ret = peripheral_gdbus_uart_open(handle, port);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to open uart port, ret : %d", ret);
		free(handle);
		handle = NULL;
		return ret;
	}

	ret = peripheral_interface_uart_init(handle);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to initialize the uart");
		peripheral_uart_close(handle);
		return ret;
	}

	*uart = handle;

	return PERIPHERAL_ERROR_NONE;
}

/**
 * @brief Destory the uart handle and release the communication.
 */
int peripheral_uart_close(peripheral_uart_h uart)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");

	ret = peripheral_gdbus_uart_close(uart);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to close uart communication, continuing anyway, ret : %d", ret);
		return ret;
	}

	peripheral_interface_uart_close(uart);

	free(uart);
	uart = NULL;

	return ret;
}

/**
 * @brief Sets baudrate of the uart device.
 */
int peripheral_uart_set_baud_rate(peripheral_uart_h uart, peripheral_uart_baud_rate_e baud)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF((baud < PERIPHERAL_UART_BAUD_RATE_0) || (baud > PERIPHERAL_UART_BAUD_RATE_230400), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid baud input");

	return peripheral_interface_uart_set_baud_rate(uart, baud);
}

int peripheral_uart_set_byte_size(peripheral_uart_h uart, peripheral_uart_byte_size_e byte_size)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF((byte_size < PERIPHERAL_UART_BYTE_SIZE_5BIT) || (byte_size > PERIPHERAL_UART_BYTE_SIZE_8BIT), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_uart_set_byte_size(uart, byte_size);
}

int peripheral_uart_set_parity(peripheral_uart_h uart, peripheral_uart_parity_e parity)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF((parity < PERIPHERAL_UART_PARITY_NONE) || (parity > PERIPHERAL_UART_PARITY_ODD), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_uart_set_parity(uart, parity);
}

int peripheral_uart_set_stop_bits(peripheral_uart_h uart, peripheral_uart_stop_bits_e stop_bits)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF((stop_bits < PERIPHERAL_UART_STOP_BITS_1BIT) || (stop_bits > PERIPHERAL_UART_STOP_BITS_2BIT), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_uart_set_stop_bits(uart, stop_bits);
}

/**
 * @brief Sets baudrate of the uart device.
 */
int peripheral_uart_set_flow_control(peripheral_uart_h uart, peripheral_uart_software_flow_control_e sw_flow_control, peripheral_uart_hardware_flow_control_e hw_flow_control)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF((sw_flow_control < PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE) || (sw_flow_control > PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid sw_flow_control parameter");
	RETVM_IF((hw_flow_control < PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE) || (hw_flow_control > PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_AUTO_RTSCTS), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid hw_flow_control parameter");

	return peripheral_interface_uart_set_flow_control(uart, sw_flow_control, hw_flow_control);
}

/**
 * @brief Reads data from the uart device.
 */
int peripheral_uart_read(peripheral_uart_h uart, uint8_t *data, uint32_t length)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF(data == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_uart_read(uart, data, length);
}

/**
 * @brief Write data to the uart device.
 */
int peripheral_uart_write(peripheral_uart_h uart, uint8_t *data, uint32_t length)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "UART feature is not supported");
	RETVM_IF(uart == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "uart handle is NULL");
	RETVM_IF(data == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_uart_write(uart, data, length);
}
