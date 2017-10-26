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

#ifndef __TEST_PERIPHERAL_SPI_H__
#define __TEST_PERIPHERAL_SPI_H__

int test_peripheral_io_spi_initialize(char *model, bool feature);

int test_peripheral_io_spi_peripheral_spi_open_p(void);
int test_peripheral_io_spi_peripheral_spi_open_n1(void);
int test_peripheral_io_spi_peripheral_spi_open_n2(void);
int test_peripheral_io_spi_peripheral_spi_open_n3(void);
int test_peripheral_io_spi_peripheral_spi_close_p(void);
int test_peripheral_io_spi_peripheral_spi_close_n(void);
int test_peripheral_io_spi_peripheral_spi_set_mode_p1(void);
int test_peripheral_io_spi_peripheral_spi_set_mode_p2(void);
int test_peripheral_io_spi_peripheral_spi_set_mode_p3(void);
int test_peripheral_io_spi_peripheral_spi_set_mode_p4(void);
int test_peripheral_io_spi_peripheral_spi_set_mode_n1(void);
int test_peripheral_io_spi_peripheral_spi_set_mode_n2(void);
int test_peripheral_io_spi_peripheral_spi_set_mode_n3(void);
int test_peripheral_io_spi_peripheral_spi_set_bit_order_p1(void);
int test_peripheral_io_spi_peripheral_spi_set_bit_order_p2(void);
int test_peripheral_io_spi_peripheral_spi_set_bit_order_n1(void);
int test_peripheral_io_spi_peripheral_spi_set_bit_order_n2(void);
int test_peripheral_io_spi_peripheral_spi_set_bit_order_n3(void);
int test_peripheral_io_spi_peripheral_spi_set_bits_per_word_p(void);
int test_peripheral_io_spi_peripheral_spi_set_bits_per_word_n1(void);
int test_peripheral_io_spi_peripheral_spi_set_bits_per_word_n2(void);
int test_peripheral_io_spi_peripheral_spi_set_frequency_p(void);
int test_peripheral_io_spi_peripheral_spi_set_frequency_n(void);
int test_peripheral_io_spi_peripheral_spi_read_p(void);
int test_peripheral_io_spi_peripheral_spi_read_n1(void);
int test_peripheral_io_spi_peripheral_spi_read_n2(void);
int test_peripheral_io_spi_peripheral_spi_write_p(void);
int test_peripheral_io_spi_peripheral_spi_write_n1(void);
int test_peripheral_io_spi_peripheral_spi_write_n2(void);
int test_peripheral_io_spi_peripheral_spi_transfer_p(void);
int test_peripheral_io_spi_peripheral_spi_transfer_n1(void);
int test_peripheral_io_spi_peripheral_spi_transfer_n2(void);
int test_peripheral_io_spi_peripheral_spi_transfer_n3(void);

#endif /* __TEST_PERIPHERAL_SPI_H__ */