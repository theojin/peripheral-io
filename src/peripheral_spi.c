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
#include "peripheral_gdbus_spi.h"
#include "peripheral_interface_spi.h"
#include "peripheral_log.h"

#define PERIPHERAL_IO_SPI_FEATURE "http://tizen.org/feature/peripheral_io.spi"

#define SPI_FEATURE_UNKNOWN -1
#define SPI_FEATURE_FALSE    0
#define SPI_FEATURE_TRUE     1

static int spi_feature = SPI_FEATURE_UNKNOWN;

static bool __is_feature_supported(void)
{
	int ret = SYSTEM_INFO_ERROR_NONE;
	bool feature = false;

	if (spi_feature == SPI_FEATURE_UNKNOWN) {
		ret = system_info_get_platform_bool(PERIPHERAL_IO_SPI_FEATURE, &feature);
		RETVM_IF(ret != SYSTEM_INFO_ERROR_NONE, false, "Failed to get system info");

		spi_feature = (feature ? SPI_FEATURE_TRUE : SPI_FEATURE_FALSE);
	}

	return (spi_feature == SPI_FEATURE_TRUE ? true : false);
}

int peripheral_spi_open(int bus, int cs, peripheral_spi_h *spi)
{
	peripheral_spi_h handle;
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid spi handle");
	RETVM_IF(bus < 0 || cs < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	/* Initialize */
	handle = (peripheral_spi_h)calloc(1, sizeof(struct _peripheral_spi_s));
	if (handle == NULL) {
		_E("Failed to allocate peripheral_spi_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

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

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	ret = peripheral_gdbus_spi_close();
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to close SPI device, continuing anyway, ret : %d", ret);
		return ret;
	}

	peripheral_interface_spi_close(spi);

	free(spi);
	spi = NULL;

	return ret;
}

int peripheral_spi_set_mode(peripheral_spi_h spi, peripheral_spi_mode_e mode)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");
	RETVM_IF((mode < PERIPHERAL_SPI_MODE_0) || (mode > PERIPHERAL_SPI_MODE_3), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid spi mode parameter");

	return peripheral_interface_spi_set_mode(spi, mode);
}

int peripheral_spi_set_bit_order(peripheral_spi_h spi, peripheral_spi_bit_order_e bit_order)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");
	RETVM_IF((bit_order < PERIPHERAL_SPI_BIT_ORDER_MSB) || (bit_order > PERIPHERAL_SPI_BIT_ORDER_LSB), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid bit order parameter");

	return peripheral_interface_spi_set_bit_order(spi, bit_order);
}

int peripheral_spi_set_bits_per_word(peripheral_spi_h spi, uint8_t bits)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	return peripheral_interface_spi_set_bits_per_word(spi, bits);
}

int peripheral_spi_set_frequency(peripheral_spi_h spi, uint32_t freq_hz)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");

	return peripheral_interface_spi_set_frequency(spi, freq_hz);
}

int peripheral_spi_read(peripheral_spi_h spi, uint8_t *data, uint32_t length)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");
	RETVM_IF(data == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_spi_read(spi, data, length);
}

int peripheral_spi_write(peripheral_spi_h spi, uint8_t *data, uint32_t length)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");
	RETVM_IF(data == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_spi_write(spi, data, length);
}

int peripheral_spi_transfer(peripheral_spi_h spi, uint8_t *txdata, uint8_t *rxdata, uint32_t length)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "SPI feature is not supported");
	RETVM_IF(spi == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "spi handle is NULL");
	RETVM_IF(txdata == NULL || rxdata == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid parameter");

	return peripheral_interface_spi_transfer(spi, txdata, rxdata, length);
}
