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

#ifndef __SPI_H__
#define __SPI_H__

#include "peripheral_io.h"

int spi_close(peripheral_spi_h spi);
int spi_set_mode(peripheral_spi_h spi, unsigned char mode);
int spi_set_bit_order(peripheral_spi_h spi, unsigned char lsb);
int spi_set_bits_per_word(peripheral_spi_h spi, unsigned char bits);
int spi_set_frequency(peripheral_spi_h spi, unsigned int freq);
int spi_read(peripheral_spi_h spi, unsigned char *rxbuf, int length);
int spi_write(peripheral_spi_h spi, unsigned char *txbuf, int length);
int spi_transfer(peripheral_spi_h spi, unsigned char *txbuf, unsigned char *rxbuf, int length);

#endif /* __SPI_H__ */
