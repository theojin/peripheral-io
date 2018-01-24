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
#define UART_BYTEINFO_SIZE	4

static const int peripheral_uart_br[UART_BAUDRATE_SIZE] = {
	B0,			B50,		B75,		B110,		B134,
	B150,		B200,		B300,		B600,		B1200,
	B1800,		B2400,		B4800,		B9600,		B19200,
	B38400,		B57600,		B115200,	B230400
};

static const int byteinfo[UART_BYTEINFO_SIZE] = {CS5, CS6, CS7, CS8};

int peripheral_interface_uart_init(peripheral_uart_h uart)
{
	int ret;
	struct termios tio;

	/*
	 * TCIOFLUSH
	 * : Flushes both input and output data queue.
	 */
	ret = tcflush(uart->fd, TCIOFLUSH);
	CHECK_ERROR(ret != 0);

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	/*
	 * c_iflag
	 * : Input mode. Each bit in c_iflag indicates an input attribute.
	 *
	 * IGNPAR
	 * : Ignores input characters (other than BREAK) that have parity errors.
	 */
	tio.c_iflag = IGNPAR;

	/*
	 * c_oflag
	 * : Output mode. Each bit in c_oflag indicates an output attribute.
	 */
	tio.c_oflag = 0;

	/*
	 * c_cflag
	 * : Control mode. Each bit in c_cflag indicates a control attribute.
	 *
	 * CLOCAL
	 * : Ignores modem status lines. A call to open() returns immediately
	 *   without waiting for a modem connection to complete. If this bit is
	 *   set to 0, modem status lines are monitored and open() waits for the
	 *   modem connection.
	 *
	 * CREAD
	 * : Enables reception. If this bit is set to 0, no input characters are
	 *   received from the terminal.
	 */
	tio.c_cflag = CLOCAL | CREAD;

	/*
	 * c_lflag - Local mode
	 */
	tio.c_lflag = 0;

	/*
	 * c_cc[]
	 * : Control characters. This is an array of characters that may have
	 *   special meaning for terminal handling.
	 *
	 * VMIN
	 * : Minimun number of characters for noncanonical read.
	 *   It is used to determine the minimun number of useful bytes
	 *   that must be accepted in the input queue before read is returned.
	 *
	 * VTIME
	 * : Timeout in deciseconds for noncanonical read.
	 *   It is used to determines how long to wait for input.
	 *
	 * case 1: c_cc[VMIN] = 0 and c_cc[VTIME] = 0
	 * : If data is available, read() returns immediately, with the lesser of
	 *   the number of bytes available, or the number of bytes requested. If no
	 *   data is available, read() returns 0.
	 *
	 * case 2: c_cc[VMIN] > 0 and c_cc[VTIME] = 0
	 * : read() blocks until the lesser of MIN bytes or the number of bytes
	 *   requested are available, and returns the lesser of these two values.
	 *
	 * case 3: c_cc[VMIN] = 0 and c_cc[VTIME] > 0
	 * : TIME specifies the limit for a timer in tenths of a seconds. The timer
	 *   is started when read() is called. read() returns either when at least
	 *   one byte of data is avalilable, or when the timer expires. If the
	 *   timer expires without any input becomming available, read() returns 0.
	 *
	 * case 4: c_cc[VMIN] > 0 and c_cc[VTIME] > 0
	 * : TIME specifies the limit for a timer in tenths of a second. Once an
	 *   initial byte of input becomes available, the timer is restarted after
	 *   each further byte is received. read() returns either when the lesser
	 *   of the number of bytes requested or MIN byte have been read, or when
	 *   the inter-byte timeout expires. Because the timer is only started
	 *   after the initial byte becomes available, at least one byte will be read.
	 */
	tio.c_cc[VMIN] = 1;
	tio.c_cc[VTIME] = 0;

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

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

	tio.c_cflag &= ~__MAX_BAUD;
	tio.c_cflag |= peripheral_uart_br[baud];

	peripheral_interface_uart_flush(uart);

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_uart_get_baud_rate(peripheral_uart_h uart, peripheral_uart_baud_rate_e *out_baud)
{
	int ret;
	struct termios tio;
	int baud;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	baud = tio.c_cflag & __MAX_BAUD;

	for (int index = 0; index < UART_BAUDRATE_SIZE; index++) {
		if (baud == peripheral_uart_br[index]) {
			*out_baud = (peripheral_uart_baud_rate_e)index;
			return PERIPHERAL_ERROR_NONE;
		}
	}

	return PERIPHERAL_ERROR_UNKNOWN;
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

	peripheral_interface_uart_flush(uart);

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	CHECK_ERROR(ret != 0);

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_interface_uart_get_byte_size(peripheral_uart_h uart, peripheral_uart_byte_size_e *out_byte_size)
{
	int ret;
	struct termios tio;
	int byte_size;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	byte_size = tio.c_cflag & CSIZE;

	for (int index = 0; index < UART_BYTEINFO_SIZE; index++) {
		if (byte_size == byteinfo[index]) {
			*out_byte_size = (peripheral_uart_byte_size_e)index;
			return PERIPHERAL_ERROR_NONE;
		}
	}

	return PERIPHERAL_ERROR_UNKNOWN;
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

int peripheral_interface_uart_get_parity(peripheral_uart_h uart, peripheral_uart_parity_e *out_parity)
{
	int ret;
	struct termios tio;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	if (tio.c_cflag & PARENB) {
		if (tio.c_cflag & PARODD) {
			*out_parity = PERIPHERAL_UART_PARITY_ODD;
		} else  {
			*out_parity = PERIPHERAL_UART_PARITY_EVEN;
		}
	} else {
		*out_parity = PERIPHERAL_UART_PARITY_NONE;
	}

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

int peripheral_interface_uart_get_stop_bits(peripheral_uart_h uart, peripheral_uart_stop_bits_e *out_stop_bits)
{
	int ret;
	struct termios tio;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	if (tio.c_cflag & CSTOPB) {
		*out_stop_bits = PERIPHERAL_UART_STOP_BITS_2BIT;
	} else {
		*out_stop_bits = PERIPHERAL_UART_STOP_BITS_1BIT;
	}

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

int peripheral_interface_uart_get_flow_control(peripheral_uart_h uart, peripheral_uart_software_flow_control_e *out_xonxoff, peripheral_uart_hardware_flow_control_e *out_rtscts)
{
	int ret;
	struct termios tio;

	ret = tcgetattr(uart->fd, &tio);
	CHECK_ERROR(ret != 0);

	if (tio.c_cflag & CRTSCTS) {
		*out_rtscts = PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_AUTO_RTSCTS;
	} else {
		*out_rtscts = PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE;
	}

	if (tio.c_iflag & (IXON | IXOFF | IXANY)) {
		*out_xonxoff = PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF;
	} else {
		*out_xonxoff = PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE;
	}

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
