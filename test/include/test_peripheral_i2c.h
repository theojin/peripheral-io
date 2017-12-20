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

#ifndef __TEST_PERIPHERAL_I2C_H__
#define __TEST_PERIPHERAL_I2C_H__

int test_peripheral_io_i2c_initialize(char *model, bool feature);

int test_peripheral_io_i2c_peripheral_i2c_open_p(void);
int test_peripheral_io_i2c_peripheral_i2c_open_n1(void);
int test_peripheral_io_i2c_peripheral_i2c_open_n2(void);
int test_peripheral_io_i2c_peripheral_i2c_open_n3(void);
int test_peripheral_io_i2c_peripheral_i2c_close_p(void);
int test_peripheral_io_i2c_peripheral_i2c_close_n(void);
int test_peripheral_io_i2c_peripheral_i2c_read_p(void);
int test_peripheral_io_i2c_peripheral_i2c_read_n1(void);
int test_peripheral_io_i2c_peripheral_i2c_read_n2(void);
int test_peripheral_io_i2c_peripheral_i2c_write_p(void);
int test_peripheral_io_i2c_peripheral_i2c_write_n1(void);
int test_peripheral_io_i2c_peripheral_i2c_write_n2(void);
int test_peripheral_io_i2c_peripheral_i2c_read_register_byte_p(void);
int test_peripheral_io_i2c_peripheral_i2c_read_register_byte_n1(void);
int test_peripheral_io_i2c_peripheral_i2c_read_register_byte_n2(void);
int test_peripheral_io_i2c_peripheral_i2c_write_register_byte_p(void);
int test_peripheral_io_i2c_peripheral_i2c_write_register_byte_n(void);
int test_peripheral_io_i2c_peripheral_i2c_read_register_word_p(void);
int test_peripheral_io_i2c_peripheral_i2c_read_register_word_n1(void);
int test_peripheral_io_i2c_peripheral_i2c_read_register_word_n2(void);
int test_peripheral_io_i2c_peripheral_i2c_write_register_word_p(void);
int test_peripheral_io_i2c_peripheral_i2c_write_register_word_n(void);

#endif /* __TEST_PERIPHERAL_I2C_H__ */