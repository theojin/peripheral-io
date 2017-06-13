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

#include "peripheral_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "peripheral_io.h"
#include "peripheral_gdbus_spi.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

int peripheral_spi_open(int bus, int cs, peripheral_spi_h *spi)
{
	peripheral_spi_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(bus < 0 || cs < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	/* Initialize */
	handle = (peripheral_spi_h)calloc(1, sizeof(struct _peripheral_spi_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_spi_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	spi_proxy_init();

	ret = peripheral_gdbus_spi_open(handle, bus, cs);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("SPI open error (%d, %d)", bus, cs);
		free(handle);
		handle = NULL;
	}
	*spi = handle;

	return ret;
}

int peripheral_spi_close(peripheral_spi_h spi)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_close(spi);
	if (ret < PERIPHERAL_ERROR_NONE)
		_E("Failed to close SPI device, continuing anyway, ret : %d", ret);

	spi_proxy_deinit();
	free(spi);

	return ret;
}

int peripheral_spi_set_mode(peripheral_spi_h spi, peripheral_spi_mode_e mode)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");
	RETVM_IF(mode > PERIPHERAL_SPI_MODE_3, PERIPHERAL_ERROR_INVALID_PARAMETER,
		"Invalid spi mode parameter");

	ret = peripheral_gdbus_spi_set_mode(spi, mode);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set mode, ret : %d", ret);

	return ret;
}

int peripheral_spi_get_mode(peripheral_spi_h spi, peripheral_spi_mode_e *mode)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_get_mode(spi, mode);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get spi mode, ret : %d", ret);

	return ret;
}

int peripheral_spi_set_lsb_first(peripheral_spi_h spi, bool lsb)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_set_lsb_first(spi, lsb);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set lsb first, ret : %d", ret);

	return ret;
}

int peripheral_spi_get_lsb_first(peripheral_spi_h spi, bool *lsb)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_get_lsb_first(spi, lsb);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get lsb first, ret : %d", ret);

	return ret;
}

int peripheral_spi_set_bits_per_word(peripheral_spi_h spi, unsigned char bits)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_set_bits(spi, bits);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set bits per word, ret : %d", ret);

	return ret;
}

int peripheral_spi_get_bits_per_word(peripheral_spi_h spi, unsigned char *bits)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_get_bits(spi, bits);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get bits per word, ret : %d", ret);

	return ret;
}

int peripheral_spi_set_frequency(peripheral_spi_h spi, unsigned int freq)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_set_frequency(spi, freq);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set frequency, ret : %d", ret);

	return ret;
}

int peripheral_spi_get_frequency(peripheral_spi_h spi, unsigned int *freq)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_get_frequency(spi, freq);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get spi frequency, ret : %d", ret);

	return ret;
}

int peripheral_spi_read(peripheral_spi_h spi, unsigned char *data, int length)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_read(spi, data, length);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to read from spi device, ret : %d", ret);

	return ret;
}

int peripheral_spi_write(peripheral_spi_h spi, unsigned char *data, int length)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_write(spi, data, length);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to write to spi device, ret : %d", ret);

	return ret;
}

int peripheral_spi_read_write(peripheral_spi_h spi, unsigned char *txdata, unsigned char *rxdata, int length)
{
	int ret;

	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_read_write(spi, txdata, rxdata, length);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to read and write, ret : %d", ret);

	return ret;
}
