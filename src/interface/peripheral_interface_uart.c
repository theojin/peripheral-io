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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#include "peripheral_interface_uart.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

#define PATH_BUF_MAX		64
#define UART_BUF_MAX		16

#define UART_BAUDRATE_SIZE	19

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif
#define MAX_ERR_LEN 128

char *sysfs_uart_path[] = {
	"/dev/ttyS",
	"/dev/ttyAMA",
	"/dev/ttySAC",
};

static const int peripheral_uart_br[UART_BAUDRATE_SIZE] = {
	B0,			B50,		B75,		B110,		B134,
	B150,		B200,		B300,		B600,		B1200,
	B1800,		B2400,		B4800,		B9600,		B19200,
	B38400,		B57600,		B115200,	B230400
};

static const int byteinfo[4] = {CS5, CS6, CS7, CS8};

int peripheral_interface_uart_close(peripheral_uart_h uart)
{
	int status;

	_D("file_hndl : %d", uart->fd);

	if (uart->fd < 0) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	status = peripheral_interface_uart_flush(uart);
	if (status < 0) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("Failed to close fd : %d, errmsg : %s", uart->fd, errmsg);
		return -EIO;
	}

	status = close(uart->fd);
	if (status < 0) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("Failed to close fd : %d, errmsg : %s", uart->fd, errmsg);
		return -EIO;
	}

	return 0;
}

int peripheral_interface_uart_flush(peripheral_uart_h uart)
{
	int ret;

	if (!uart->fd) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	ret = tcflush(uart->fd, TCIOFLUSH);
	if (ret < 0) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcflush failed, errmsg : %s", errmsg);
		return -1;
	}

	return 0;
}

int peripheral_interface_uart_set_baud_rate(peripheral_uart_h uart, uart_baud_rate_e baud)
{
	int ret;
	struct termios tio;

	_D("file_hndl : %d, baud : %d", uart->fd, baud);

	memset(&tio, 0, sizeof(tio));
	if (!uart->fd) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	if (baud > UART_BAUD_RATE_230400) {
		_E("Invalid parameter");
		return -EINVAL;
	}

	ret = tcgetattr(uart->fd, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcgetattr failed, errmsg : %s", errmsg);
		return -1;
	}
	tio.c_cflag = peripheral_uart_br[baud];
	tio.c_iflag = IGNPAR;
	tio.c_oflag = 0;
	tio.c_lflag = 0;
	tio.c_cc[VMIN] = 1;
	tio.c_cc[VTIME] = 0;

	peripheral_interface_uart_flush(uart);
	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcsetattr failed, errmsg: %s", errmsg);
		return -1;
	}

	return 0;
}

int peripheral_interface_uart_set_byte_size(peripheral_uart_h uart, uart_byte_size_e byte_size)
{
	int ret;
	struct termios tio;

	_D("file_hndl : %d, bytesize : %d", uart->fd, byte_size);

	if (!uart->fd) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	if (byte_size > UART_BYTE_SIZE_8BIT) {
		_E("Invalid bytesize parameter");
		return -EINVAL;
	}

	ret = tcgetattr(uart->fd, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcgetattr failed, errmsg: %s", errmsg);
		return -1;
	}

	/* set byte size */
	tio.c_cflag &= ~CSIZE;
	tio.c_cflag |= byteinfo[byte_size];
	tio.c_cflag |= (CLOCAL | CREAD);

	peripheral_interface_uart_flush(uart);
	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcsetattr failed, errmsg : %s", errmsg);
		return -1;
	}

	return 0;
}

int peripheral_interface_uart_set_parity(peripheral_uart_h uart, uart_parity_e parity)
{
	int ret;
	struct termios tio;

	_D("file_hndl : %d, parity : %d", uart->fd, parity);

	if (!uart->fd) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	ret = tcgetattr(uart->fd, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcgetattr failed, errmsg: %s", errmsg);
		return -1;
	}

	/* set parity info */
	switch (parity) {
	case UART_PARITY_EVEN:
		tio.c_cflag |= PARENB;
		tio.c_cflag &= ~PARODD;
		break;
	case UART_PARITY_ODD:
		tio.c_cflag |= PARENB;
		tio.c_cflag |= PARODD;
		break;
	case UART_PARITY_NONE:
	default:
		tio.c_cflag &= ~PARENB;
		tio.c_cflag &= ~PARODD;
		break;
	}

	peripheral_interface_uart_flush(uart);
	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcsetattr failed, errmsg : %s", errmsg);
		return -1;
	}

	return 0;
}

int peripheral_interface_uart_set_stop_bits(peripheral_uart_h uart, uart_stop_bits_e stop_bits)
{
	int ret;
	struct termios tio;

	_D("file_hndl : %d, stopbits : %d", uart->fd, stop_bits);

	if (!uart->fd) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	ret = tcgetattr(uart->fd, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcgetattr failed, errmsg: %s", errmsg);
		return -1;
	}

	/* set stop bit */
	switch (stop_bits) {
	case UART_STOP_BITS_1BIT:
		tio.c_cflag &= ~CSTOPB;
		break;
	case UART_STOP_BITS_2BIT:
		tio.c_cflag |= CSTOPB;
		break;
	default:
		_E("Invalid parameter stop_bits");
		return -EINVAL;
	}

	peripheral_interface_uart_flush(uart);
	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcsetattr failed, errmsg : %s", errmsg);
		return -1;
	}

	return 0;
}

int peripheral_interface_uart_set_flow_control(peripheral_uart_h uart, bool xonxoff, bool rtscts)
{
	int ret;
	struct termios tio;

	_D("file_hndl : %d, xonxoff : %d, rtscts : %d", uart->fd, xonxoff, rtscts);

	if (!uart->fd) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	ret = tcgetattr(uart->fd, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcgetattr failed, errmsg : %s", errmsg);
		return -1;
	}

	/* rtscts => 1: rts/cts on, 0: off */
	if (rtscts)
		tio.c_cflag |= CRTSCTS;
	else
		tio.c_cflag &= ~CRTSCTS;

	/* xonxoff => 1: xon/xoff on, 0: off */
	if (xonxoff)
		tio.c_iflag |= (IXON | IXOFF | IXANY);
	else
		tio.c_iflag &= ~(IXON | IXOFF | IXANY);

	ret = tcsetattr(uart->fd, TCSANOW, &tio);
	if (ret) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("tcsetattr failed, errmsg : %s", errmsg);
		return -1;
	}

	return 0;
}

int peripheral_interface_uart_read(peripheral_uart_h uart, uint8_t *buf, unsigned int length)
{
	int ret;

	if (!uart->fd) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	ret = read(uart->fd, (void *)buf, length);
	if (ret <= 0) {
		if (errno == EAGAIN)
			return -EAGAIN;
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("read failed, errmsg : %s", errmsg);
		return -EIO;
	}

	return ret;
}

int peripheral_interface_uart_write(peripheral_uart_h uart, uint8_t *buf, unsigned int length)
{
	int ret;

	if (!uart->fd) {
		_E("Invalid NULL parameter");
		return -EINVAL;
	}

	ret = write(uart->fd, buf, length);
	if (ret <= 0) {
		if (errno == EAGAIN)
			return -EAGAIN;
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("write failed, errmsg : %s", errmsg);
		return -EIO;
	}

	return ret;
}
