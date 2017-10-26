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

#include <stdio.h>
#include <string.h>
#include <peripheral_io.h>
#include "test_peripheral_uart.h"

#define UART_PORT_RPI3 0
#define UART_PORT_ARTIK530 4
#define UART_PORT_INVALID -99
#define UART_BUFFER_LEN 10
#define	UART_WRITE_DATA 0x00

static bool g_feature = true;
static int port;

int test_peripheral_io_uart_initialize(char *model, bool feature)
{
	g_feature = feature;

	if (!strcmp(model, "rpi3"))
		port = UART_PORT_RPI3;
	else if (!strcmp(model, "artik"))
		port = UART_PORT_ARTIK530;
	else
		return -1;

	return 0;
}

int test_peripheral_io_uart_peripheral_uart_open_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_open_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_open(UART_PORT_INVALID, &uart_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(UART_PORT_INVALID, &uart_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_open_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_uart_open(port, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_close_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_close_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_uart_close(NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_close(NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_0);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_0);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_50);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_50);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_110);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_110);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p4(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_134);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_134);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p5(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_150);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_150);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p6(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_200);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_200);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p7(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_300);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_300);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p8(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_600);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_600);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p9(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_1200);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_1200);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p10(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_1800);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_1800);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p11(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_2400);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_2400);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p12(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_4800);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_4800);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p13(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_9600);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_9600);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p14(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_19200);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_19200);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p15(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_38400);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_38400);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p16(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_57600);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_57600);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p17(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_115200);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_115200);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_p18(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_230400);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_230400);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(NULL, PERIPHERAL_UART_BAUD_RATE_1200);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_set_baud_rate(NULL, PERIPHERAL_UART_BAUD_RATE_1200);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_0 - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_0 - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_baud_rate_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_230400 + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_baud_rate(uart_h, PERIPHERAL_UART_BAUD_RATE_230400 + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_byte_size_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_5BIT);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_5BIT);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_byte_size_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_6BIT);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_6BIT);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_byte_size_p3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_7BIT);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_7BIT);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_byte_size_p4(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_8BIT);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_8BIT);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_byte_size_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_uart_set_byte_size(NULL, PERIPHERAL_UART_BYTE_SIZE_5BIT);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_set_byte_size(NULL, PERIPHERAL_UART_BYTE_SIZE_5BIT);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_byte_size_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_5BIT - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_5BIT - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_byte_size_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_8BIT + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_byte_size(uart_h, PERIPHERAL_UART_BYTE_SIZE_8BIT + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_parity_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_NONE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_NONE);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_parity_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_EVEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_EVEN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_parity_p3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_ODD);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_ODD);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_parity_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_uart_set_parity(NULL, PERIPHERAL_UART_PARITY_NONE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_set_parity(NULL, PERIPHERAL_UART_PARITY_NONE);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_parity_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_NONE - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_NONE - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_parity_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_ODD + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_parity(uart_h, PERIPHERAL_UART_PARITY_ODD + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_stop_bits_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_stop_bits(uart_h, PERIPHERAL_UART_STOP_BITS_1BIT);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_stop_bits(uart_h, PERIPHERAL_UART_STOP_BITS_1BIT);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_stop_bits_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_stop_bits(uart_h, PERIPHERAL_UART_STOP_BITS_2BIT);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_stop_bits(uart_h, PERIPHERAL_UART_STOP_BITS_2BIT);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_stop_bits_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_uart_set_stop_bits(NULL, PERIPHERAL_UART_STOP_BITS_1BIT);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_set_stop_bits(NULL, PERIPHERAL_UART_STOP_BITS_1BIT);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_stop_bits_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_stop_bits(uart_h, PERIPHERAL_UART_STOP_BITS_1BIT - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_stop_bits(uart_h, PERIPHERAL_UART_STOP_BITS_1BIT - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_stop_bits_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_stop_bits(uart_h, PERIPHERAL_UART_STOP_BITS_2BIT + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_stop_bits(uart_h, PERIPHERAL_UART_STOP_BITS_2BIT + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_AUTO_RTSCTS);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_AUTO_RTSCTS);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_p3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_p4(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_AUTO_RTSCTS);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_AUTO_RTSCTS);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(NULL, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_set_flow_control(NULL, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE - 1, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE - 1, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF + 1, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF + 1, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_n4(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF, PERIPHERAL_UART_HARDWARE_FLOW_CONTROL_NONE - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_set_flow_control_n5(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_set_flow_control(uart_h, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_NONE, PERIPHERAL_UART_SOFTWARE_FLOW_CONTROL_XONXOFF + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_read_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	uint8_t data[UART_BUFFER_LEN];

	if (g_feature == false) {
		ret = peripheral_uart_read(uart_h, data, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_read(uart_h, data, UART_BUFFER_LEN);
		if (ret <= 0 && ret != PERIPHERAL_ERROR_TRY_AGAIN) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_read_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint8_t data[UART_BUFFER_LEN];

	if (g_feature == false) {
		ret = peripheral_uart_read(NULL, data, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_read(NULL, data, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_read_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_read(uart_h, NULL, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_read(uart_h, NULL, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_write_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	uint8_t data[UART_BUFFER_LEN] = {UART_WRITE_DATA, };

	if (g_feature == false) {
		ret = peripheral_uart_write(uart_h, data, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_write(uart_h, data, UART_BUFFER_LEN);
		if (ret <= 0 && ret != PERIPHERAL_ERROR_TRY_AGAIN) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_uart_peripheral_uart_write_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint8_t data[UART_BUFFER_LEN] = {UART_WRITE_DATA, };

	if (g_feature == false) {
		ret = peripheral_uart_write(NULL, data, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_write(NULL, data, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}


int test_peripheral_io_uart_peripheral_uart_write_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_uart_h uart_h = NULL;

	if (g_feature == false) {
		ret = peripheral_uart_write(uart_h, NULL, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_uart_open(port, &uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_uart_write(uart_h, NULL, UART_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_uart_close(uart_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_uart_close(uart_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}
