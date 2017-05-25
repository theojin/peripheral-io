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
#ifndef __PERIPHERAL_GDBUS_SPI_H_
#define __PERIPHERAL_GDBUS_SPI_H_

void spi_proxy_init(void);
void spi_proxy_deinit();

int peripheral_gdbus_spi_open(peripheral_spi_h spi, int bus, int cs);
int peripheral_gdbus_spi_close(peripheral_spi_h spi);
int peripheral_gdbus_spi_set_mode(peripheral_spi_h spi, peripheral_spi_mode_e mode);
int peripheral_gdbus_spi_get_mode(peripheral_spi_h spi, peripheral_spi_mode_e *mode);
int peripheral_gdbus_spi_set_lsb_first(peripheral_spi_h spi, bool lsb);
int peripheral_gdbus_spi_get_lsb_first(peripheral_spi_h spi, bool *lsb);
int peripheral_gdbus_spi_set_bits(peripheral_spi_h spi, unsigned char bits);
int peripheral_gdbus_spi_get_bits(peripheral_spi_h spi, unsigned char *bits);
int peripheral_gdbus_spi_set_frequency(peripheral_spi_h spi, unsigned int freq);
int peripheral_gdbus_spi_get_frequency(peripheral_spi_h spi, unsigned int *freq);
int peripheral_gdbus_spi_read(peripheral_spi_h spi, unsigned char *data, int length);
int peripheral_gdbus_spi_write(peripheral_spi_h spi, unsigned char *data, int length);
int peripheral_gdbus_spi_read_write(peripheral_spi_h spi, unsigned char *tx_data, unsigned char *rx_data, int length);

#endif /* __PERIPHERAL_GDBUS_SPI_H_ */
