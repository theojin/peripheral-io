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
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "peripheral_interface_common.h"
#include "peripheral_interface_spi.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

#define SYSFS_SPI_DIR "/dev/spidev"
#define SYSFS_SPI_BUFSIZ "/sys/module/spidev/parameters/bufsiz"
#define SPI_BUFFER_MAX 64
#define MAX_ERR_LEN 255

int peripheral_interface_spi_close(peripheral_spi_h spi)
{
	int status;

	_D("fd : %d", spi->fd);
	RETVM_IF(spi->fd < 0, -EINVAL, "Invalid fd");

	status = close(spi->fd);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_spi_set_mode(peripheral_spi_h spi, peripheral_spi_mode_e mode)
{
	int status;

	_D("fd : %d, mode : %d", spi->fd, mode);
	RETVM_IF(spi->fd < 0, -EINVAL, "Invalid fd");

	status = ioctl(spi->fd, SPI_IOC_WR_MODE, &mode);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_spi_set_bit_order(peripheral_spi_h spi, peripheral_spi_bit_order_e bit_order)
{
	int status;

	_D("fd : %d, lsb : %d", spi->fd, bit_order);
	RETVM_IF(spi->fd < 0, -EINVAL, "Invalid fd");

	status = ioctl(spi->fd, SPI_IOC_WR_LSB_FIRST, &bit_order);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_spi_set_bits_per_word(peripheral_spi_h spi, uint8_t bits)
{
	int status;

	_D("fd : %d, bits : %d", spi->fd, bits);
	RETVM_IF(spi->fd < 0, -EINVAL, "Invalid fd");

	status = ioctl(spi->fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_spi_set_frequency(peripheral_spi_h spi, uint32_t freq)
{
	int status;

	_D("fd : %d, freq : %d", spi->fd, freq);
	RETVM_IF(spi->fd < 0, -EINVAL, "Invalid fd");

	status = ioctl(spi->fd, SPI_IOC_WR_MAX_SPEED_HZ, &freq);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_spi_read(peripheral_spi_h spi, uint8_t *rxbuf, uint32_t length)
{
	int status;
	struct spi_ioc_transfer xfer;

	RETVM_IF(spi->fd < 0, -EINVAL, "Invalid fd : %d", spi->fd);

	memset(&xfer, 0, sizeof(struct spi_ioc_transfer));
	xfer.rx_buf = (unsigned long)rxbuf;
	xfer.len = length;

	status = ioctl(spi->fd, SPI_IOC_MESSAGE(1), &xfer);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_spi_write(peripheral_spi_h spi, uint8_t *txbuf, uint32_t length)
{
	int status;
	struct spi_ioc_transfer xfer;

	RETVM_IF(spi->fd < 0, -EINVAL, "Invalid fd : %d", spi->fd);

	memset(&xfer, 0, sizeof(struct spi_ioc_transfer));
	xfer.tx_buf = (unsigned long)txbuf;
	xfer.len = length;

	status = ioctl(spi->fd, SPI_IOC_MESSAGE(1), &xfer);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_spi_transfer(peripheral_spi_h spi, uint8_t *txbuf, uint8_t *rxbuf, uint32_t length)
{
	int status;
	struct spi_ioc_transfer xfer;

	RETVM_IF(spi->fd < 0, -EINVAL, "Invalid fd : %d", spi->fd);

	if (!txbuf || !rxbuf) return -EINVAL;

	memset(&xfer, 0, sizeof(xfer));
	xfer.tx_buf = (unsigned long)txbuf;
	xfer.rx_buf = (unsigned long)rxbuf;
	xfer.len = length;

	status = ioctl(spi->fd, SPI_IOC_MESSAGE(1), &xfer);
	CHECK_ERROR(status);

	return 0;
}
