/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
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

#include <termios.h>

#include "peripheral_interface_uart.h"

#define UART_BAUDRATE_SIZE	19

static const int peripheral_uart_br[UART_BAUDRATE_SIZE] = {
	B0,			B50,		B75,		B110,		B134,
	B150,		B200,		B300,		B600,		B1200,
	B1800,		B2400,		B4800,		B9600,		B19200,
	B38400,		B57600,		B115200,	B230400
};

static const int byteinfo[4] = {CS5, CS6, CS7, CS8};

void peripheral_interface_uart_close(peripheral_uart_h uart)
{
	peripheral_interface_uart_flush(uart);
	close(uart->fd);
}

void peripheral_interface_uart_flush(peripheral_uart_h uart)
{
	tcflush(uart->fd, TCIOFLUSH);
}

int peripheral_interface_uart_set_baud_rate(peripheral_uart_h uart, peripheral_uart_baud_rate_e baud)
{
	int ret;
	struct termios tio;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	tio.c_cflag = peripheral_uart_br[baud];
	tio.c_iflag = IGNPAR;
	tio.c_oflag = 0;
	tio.c_lflag = 0;
	tio.c_cc[VMIN] = 1;
	tio.c_cc[VTIME] = 0;

	peripheral_interface_uart_flush(uart);

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_uart_set_byte_size(peripheral_uart_h uart, peripheral_uart_byte_size_e byte_size)
{
	int ret;
	struct termios tio;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	/* set byte size */
	tio.c_cflag &= ~CSIZE;
	tio.c_cflag |= byteinfo[byte_size];
	tio.c_cflag |= (CLOCAL | CREAD);

	peripheral_interface_uart_flush(uart);

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_uart_set_parity(peripheral_uart_h uart, peripheral_uart_parity_e parity)
{
	int ret;
	struct termios tio;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	/* set parity info */
	switch (parity) {
	case PERIPHERAL_UART_PARITY_EVEN:
		tio.c_cflag |= PARENB;
		tio.c_cflag &= ~PARODD;
		break;
	case PERIPHERAL_UART_PARITY_ODD:
		tio.c_cflag |= PARENB;
		tio.c_cflag |= PARODD;
		break;
	case PERIPHERAL_UART_PARITY_NONE:
	default:
		tio.c_cflag &= ~PARENB;
		tio.c_cflag &= ~PARODD;
		break;
	}

	peripheral_interface_uart_flush(uart);

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_uart_set_stop_bits(peripheral_uart_h uart, peripheral_uart_stop_bits_e stop_bits)
{
	int ret;
	struct termios tio;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	/* set stop bit */
	switch (stop_bits) {
	case PERIPHERAL_UART_STOP_BITS_1BIT:
		tio.c_cflag &= ~CSTOPB;
		break;
	case PERIPHERAL_UART_STOP_BITS_2BIT:
		tio.c_cflag |= CSTOPB;
		break;
	default:
		_E("Invalid parameter stop_bits");
		return PERIPHERAL_ERROR_INVALID_PARAMETER;
	}

	peripheral_interface_uart_flush(uart);

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_uart_set_flow_control(peripheral_uart_h uart, peripheral_uart_software_flow_control_e xonxoff, peripheral_uart_hardware_flow_control_e rtscts)
{
	int ret;
	struct termios tio;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	if (rtscts == PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_AUTO_RTSCTS)
		tio.c_cflag |= CRTSCTS;
	else if (rtscts == PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE)
		tio.c_cflag &= ~CRTSCTS;
	else
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	if (xonxoff == PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF)
		tio.c_iflag |= (IXON | IXOFF | IXANY);
	else if (xonxoff == PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE)
		tio.c_iflag &= ~(IXON | IXOFF | IXANY);
	else
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	peripheral_interface_uart_flush(uart);

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_uart_read(peripheral_uart_h uart, uint8_t *buf, uint32_t length)
{
	int ret = read(uart->fd, (void *)buf, length);
	CHECK_ERROR(ret != length);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_uart_write(peripheral_uart_h uart, uint8_t *buf, uint32_t length)
{
	int ret = write(uart->fd, buf, length);
	CHECK_ERROR(ret != length);

	return PERIPHERAL_ERROR_NONE;
}
