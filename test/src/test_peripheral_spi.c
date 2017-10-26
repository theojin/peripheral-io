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
#include "test_peripheral_spi.h"

#define SPI_BUS_RPI3 0
#define SPI_BUS_ARTIK530 2
#define SPI_BUS_INVALID -99
#define SPI_CS 0
#define SPI_CS_INVALID -99
#define SPI_BITS_PER_WORD 8
#define SPI_BITS_PER_WORD_INVALID 1
#define SPI_FREQUENCY 15000
#define SPI_BUFFER_LEN 1
#define	SPI_WRITE_DATA 0x00

static bool g_feature = true;
static int bus;
static int cs;

int test_peripheral_io_spi_initialize(char *model, bool feature)
{
	g_feature = feature;

	if (!strcmp(model, "rpi3"))
		bus = SPI_BUS_RPI3;
	else if (!strcmp(model, "artik"))
		bus = SPI_BUS_ARTIK530;
	else
		return -1;

	cs = SPI_CS;

	return 0;
}

int test_peripheral_io_spi_peripheral_spi_open_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_open_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_open(SPI_BUS_INVALID, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(SPI_BUS_INVALID, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_open_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_open(bus, SPI_CS_INVALID, &spi_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, SPI_CS_INVALID, &spi_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_open_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_spi_open(bus, cs, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_close_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_close_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_spi_close(NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_close(NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_mode_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_0);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_0);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_mode_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_1);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_mode_p3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_2);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_2);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_mode_p4(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_3);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_3);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_mode_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_mode(NULL, PERIPHERAL_SPI_MODE_0);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_mode(NULL, PERIPHERAL_SPI_MODE_0);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_mode_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_0 - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_0 - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_mode_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_3 + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_3 + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_bit_order_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_bit_order(spi_h, PERIPHERAL_SPI_BIT_ORDER_MSB);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_bit_order(spi_h, PERIPHERAL_SPI_BIT_ORDER_MSB);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_bit_order_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_bit_order(spi_h, PERIPHERAL_SPI_BIT_ORDER_LSB);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_bit_order(spi_h, PERIPHERAL_SPI_BIT_ORDER_LSB);
		if (ret != PERIPHERAL_ERROR_IO_ERROR) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_bit_order_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_spi_set_bit_order(NULL, PERIPHERAL_SPI_BIT_ORDER_MSB);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_set_bit_order(NULL, PERIPHERAL_SPI_BIT_ORDER_MSB);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_bit_order_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_bit_order(spi_h, PERIPHERAL_SPI_BIT_ORDER_MSB - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_bit_order(spi_h, PERIPHERAL_SPI_BIT_ORDER_MSB - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_bit_order_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_bit_order(spi_h, PERIPHERAL_SPI_BIT_ORDER_LSB + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_bit_order(spi_h, PERIPHERAL_SPI_BIT_ORDER_LSB + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_bits_per_word_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_bits_per_word(spi_h, SPI_BITS_PER_WORD);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_bits_per_word(spi_h, SPI_BITS_PER_WORD);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_bits_per_word_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_spi_set_bits_per_word(NULL, SPI_BITS_PER_WORD);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_set_bits_per_word(NULL, SPI_BITS_PER_WORD);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_bits_per_word_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_bits_per_word(spi_h, SPI_BITS_PER_WORD_INVALID);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_bits_per_word(spi_h, SPI_BITS_PER_WORD_INVALID);
		if (ret != PERIPHERAL_ERROR_IO_ERROR) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_frequency_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_set_frequency(spi_h, SPI_FREQUENCY);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_set_mode(spi_h, PERIPHERAL_SPI_MODE_0);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_set_bits_per_word(spi_h, SPI_BITS_PER_WORD);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_set_frequency(spi_h, SPI_FREQUENCY);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_set_frequency_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_spi_set_frequency(NULL, SPI_FREQUENCY);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_set_frequency(NULL, SPI_FREQUENCY);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_read_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	uint8_t data;

	if (g_feature == false) {
		ret = peripheral_spi_read(spi_h, &data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_read(spi_h, &data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_read_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint8_t data;

	if (g_feature == false) {
		ret = peripheral_spi_read(NULL, &data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_read(NULL, &data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_read_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_read(spi_h, NULL, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_read(spi_h, NULL, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_write_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	uint8_t data = SPI_WRITE_DATA;

	if (g_feature == false) {
		ret = peripheral_spi_write(spi_h, &data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_write(spi_h, &data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_write_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint8_t data = SPI_WRITE_DATA;

	if (g_feature == false) {
		ret = peripheral_spi_write(NULL, &data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_write(NULL, &data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}


int test_peripheral_io_spi_peripheral_spi_write_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	if (g_feature == false) {
		ret = peripheral_spi_write(spi_h, NULL, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_write(spi_h, NULL, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_transfer_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	uint8_t tx_data = SPI_WRITE_DATA;
	uint8_t rx_data;

	if (g_feature == false) {
		ret = peripheral_spi_transfer(spi_h, &tx_data, &rx_data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_transfer(spi_h, &tx_data, &rx_data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_transfer_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint8_t tx_data = SPI_WRITE_DATA;
	uint8_t rx_data;

	if (g_feature == false) {
		ret = peripheral_spi_transfer(NULL, &tx_data, &rx_data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_transfer(NULL, &tx_data, &rx_data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_transfer_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	uint8_t rx_data;

	if (g_feature == false) {
		ret = peripheral_spi_transfer(spi_h, NULL, &rx_data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_transfer(spi_h, NULL, &rx_data, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_spi_peripheral_spi_transfer_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_spi_h spi_h = NULL;

	uint8_t tx_data = SPI_WRITE_DATA;

	if (g_feature == false) {
		ret = peripheral_spi_transfer(spi_h, &tx_data, NULL, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED) return PERIPHERAL_ERROR_UNKNOWN;

	} else {
		ret = peripheral_spi_open(bus, cs, &spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;

		ret = peripheral_spi_transfer(spi_h, &tx_data, NULL, SPI_BUFFER_LEN);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_spi_close(spi_h);
			return PERIPHERAL_ERROR_UNKNOWN;
		}

		ret = peripheral_spi_close(spi_h);
		if (ret != PERIPHERAL_ERROR_NONE) return PERIPHERAL_ERROR_UNKNOWN;
	}

	return PERIPHERAL_ERROR_NONE;
}
