
/*
 * Copyright (c) 2017-2018 Samsung Electronics Co., Ltd.
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
#include <system_info.h>

#include "peripheral_io.h"
#include "test_peripheral_gpio.h"
#include "test_peripheral_i2c.h"
#include "test_peripheral_pwm.h"
#include "test_peripheral_adc.h"
#include "test_peripheral_uart.h"
#include "test_peripheral_spi.h"

#define KEY_SYSTEM_MODEL_NAME          "http://tizen.org/system/model_name"
#define KEY_FEATURE_PERIPHERAL_IO_GPIO "http://tizen.org/feature/peripheral_io.gpio"
#define KEY_FEATURE_PERIPHERAL_IO_I2C  "http://tizen.org/feature/peripheral_io.i2c"
#define KEY_FEATURE_PERIPHERAL_IO_PWM  "http://tizen.org/feature/peripheral_io.pwm"
#define KEY_FEATURE_PERIPHERAL_IO_ADC  "http://tizen.org/feature/peripheral_io.adc"
#define KEY_FEATURE_PERIPHERAL_IO_UART "http://tizen.org/feature/peripheral_io.uart"
#define KEY_FEATURE_PERIPHERAL_IO_SPI  "http://tizen.org/feature/peripheral_io.spi"

static int fail_count = 0;
static int pass_count = 0;

static void __error_check(int ret, char *name)
{
	if (ret != PERIPHERAL_ERROR_NONE) {
		printf("[FAIL] %s\n", name);
		fail_count++;
	} else {
		printf("[PASS] %s\n", name);
		pass_count++;
	}
}

static int __get_model_name(char **model_name)
{
	int ret = SYSTEM_INFO_ERROR_NONE;
	ret = system_info_get_platform_string(KEY_SYSTEM_MODEL_NAME, model_name);
	if (ret != SYSTEM_INFO_ERROR_NONE) {
		printf("[Message] Failed to get model name.\n\n");
		return PERIPHERAL_ERROR_NOT_SUPPORTED;
	}
	return PERIPHERAL_ERROR_NONE;
}

static int __get_feature(const char *key, bool *feature)
{
	int ret = SYSTEM_INFO_ERROR_NONE;
	ret = system_info_get_platform_bool(key, feature);
	if (ret != SYSTEM_INFO_ERROR_NONE) {
		printf("[Message] Failed to feature (%s).\n\n", key);
		return PERIPHERAL_ERROR_NOT_SUPPORTED;
	}
	return PERIPHERAL_ERROR_NONE;
}

static int __test_peripheral_init()
{
	int ret = PERIPHERAL_ERROR_NONE;

	char *model_name = NULL;
	bool feature = false;

	ret = __get_model_name(&model_name);
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	ret = __get_feature(KEY_FEATURE_PERIPHERAL_IO_GPIO, &feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;
	ret = test_peripheral_io_gpio_initialize(model_name, feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;

	ret = __get_feature(KEY_FEATURE_PERIPHERAL_IO_I2C, &feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;
	ret = test_peripheral_io_i2c_initialize(model_name, feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;

	ret = __get_feature(KEY_FEATURE_PERIPHERAL_IO_PWM, &feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;
	ret = test_peripheral_io_pwm_initialize(model_name, feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;

	ret = __get_feature(KEY_FEATURE_PERIPHERAL_IO_ADC, &feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;
	ret = test_peripheral_io_adc_initialize(model_name, feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;

	ret = __get_feature(KEY_FEATURE_PERIPHERAL_IO_UART, &feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;
	ret = test_peripheral_io_uart_initialize(model_name, feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;

	ret = __get_feature(KEY_FEATURE_PERIPHERAL_IO_SPI, &feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;
	ret = test_peripheral_io_spi_initialize(model_name, feature);
	if (ret != PERIPHERAL_ERROR_NONE)
		goto ERR;

ERR:
	free(model_name);
	return ret;
}

static void __test_peripheral_gpio_run()
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = test_peripheral_io_gpio_peripheral_gpio_open_p();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_open_p");
	ret = test_peripheral_io_gpio_peripheral_gpio_open_n1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_open_n1");
	ret = test_peripheral_io_gpio_peripheral_gpio_open_n2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_open_n2");
	ret = test_peripheral_io_gpio_peripheral_gpio_close_p();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_close_p");
	ret = test_peripheral_io_gpio_peripheral_gpio_close_n();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_close_n");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_direction_p1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_direction_p1");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_direction_p2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_direction_p2");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_direction_p3();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_direction_p3");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_direction_n1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_direction_n1");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_direction_n2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_direction_n2");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_direction_n3();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_direction_n3");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p1");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p2");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p3();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p3");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p4();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p4");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n1");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n2");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n3();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n3");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_p();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_p");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_n1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_n1");
	ret = test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_n2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_n2");
	ret = test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_p1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_p1");
	ret = test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_p2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_p2");
	ret = test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_n();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_n");
	ret = test_peripheral_io_gpio_peripheral_gpio_read_p();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_read_p");
	ret = test_peripheral_io_gpio_peripheral_gpio_read_n1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_read_n1");
	ret = test_peripheral_io_gpio_peripheral_gpio_read_n2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_read_n2");
	ret = test_peripheral_io_gpio_peripheral_gpio_write_p();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_write_p");
	ret = test_peripheral_io_gpio_peripheral_gpio_write_n1();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_write_n1");
	ret = test_peripheral_io_gpio_peripheral_gpio_write_n2();
	__error_check(ret, "test_peripheral_io_gpio_peripheral_gpio_write_n2");
}

static void __test_peripheral_i2c_run()
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = test_peripheral_io_i2c_peripheral_i2c_open_p();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_open_p");
	ret = test_peripheral_io_i2c_peripheral_i2c_open_n1();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_open_n1");
	ret = test_peripheral_io_i2c_peripheral_i2c_open_n2();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_open_n2");
	ret = test_peripheral_io_i2c_peripheral_i2c_open_n3();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_open_n3");
	ret = test_peripheral_io_i2c_peripheral_i2c_close_p();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_close_p");
	ret = test_peripheral_io_i2c_peripheral_i2c_close_n();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_close_n");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_p();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_p");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_n1();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_n1");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_n2();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_n2");
	ret = test_peripheral_io_i2c_peripheral_i2c_write_p();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_write_p");
	ret = test_peripheral_io_i2c_peripheral_i2c_write_n1();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_write_n1");
	ret = test_peripheral_io_i2c_peripheral_i2c_write_n2();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_write_n2");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_register_byte_p();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_register_byte_p");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_register_byte_n1();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_register_byte_n1");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_register_byte_n2();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_register_byte_n2");
	ret = test_peripheral_io_i2c_peripheral_i2c_write_register_byte_p();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_write_register_byte_p");
	ret = test_peripheral_io_i2c_peripheral_i2c_write_register_byte_n();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_write_register_byte_n");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_register_word_p();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_register_word_p");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_register_word_n1();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_register_word_n1");
	ret = test_peripheral_io_i2c_peripheral_i2c_read_register_word_n2();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_read_register_word_n2");
	ret = test_peripheral_io_i2c_peripheral_i2c_write_register_word_p();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_write_register_word_p");
	ret = test_peripheral_io_i2c_peripheral_i2c_write_register_word_n();
	__error_check(ret, "test_peripheral_io_i2c_peripheral_i2c_write_register_word_n");
}

static void __test_peripheral_pwm_run()
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = test_peripheral_io_pwm_peripheral_pwm_open_p();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_open_p");
	ret = test_peripheral_io_pwm_peripheral_pwm_open_n1();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_open_n1");
	ret = test_peripheral_io_pwm_peripheral_pwm_open_n2();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_open_n2");
	ret = test_peripheral_io_pwm_peripheral_pwm_open_n3();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_open_n3");
	ret = test_peripheral_io_pwm_peripheral_pwm_close_p();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_close_p");
	ret = test_peripheral_io_pwm_peripheral_pwm_close_n();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_close_n");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_period_p();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_period_p");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_period_n();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_period_n");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_duty_cycle_p();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_duty_cycle_p");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_duty_cycle_n();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_duty_cycle_n");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_polarity_p1();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_polarity_p1");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_polarity_p2();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_polarity_p2");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_polarity_n1();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_polarity_n1");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_polarity_n2();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_polarity_n2");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_polarity_n3();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_polarity_n3");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_enabled_p1();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_enabled_p1");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_enabled_p2();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_enabled_p2");
	ret = test_peripheral_io_pwm_peripheral_pwm_set_enabled_n();
	__error_check(ret, "test_peripheral_io_pwm_peripheral_pwm_set_enabled_n");
}

static void __test_peripheral_adc_run()
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = test_peripheral_io_adc_peripheral_adc_open_p();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_open_p");
	ret = test_peripheral_io_adc_peripheral_adc_open_n1();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_open_n1");
	ret = test_peripheral_io_adc_peripheral_adc_open_n2();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_open_n2");
	ret = test_peripheral_io_adc_peripheral_adc_open_n3();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_open_n3");
	ret = test_peripheral_io_adc_peripheral_adc_close_p();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_close_p");
	ret = test_peripheral_io_adc_peripheral_adc_close_n();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_close_n");
	ret = test_peripheral_io_adc_peripheral_adc_read_p();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_read_p");
	ret = test_peripheral_io_adc_peripheral_adc_read_n1();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_read_n1");
	ret = test_peripheral_io_adc_peripheral_adc_read_n2();
	__error_check(ret, "test_peripheral_io_adc_peripheral_adc_read_n2");
}

static void __test_peripheral_uart_run()
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = test_peripheral_io_uart_peripheral_uart_open_p();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_open_p");
	ret = test_peripheral_io_uart_peripheral_uart_open_n1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_open_n1");
	ret = test_peripheral_io_uart_peripheral_uart_open_n2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_open_n2");
	ret = test_peripheral_io_uart_peripheral_uart_close_p();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_close_p");
	ret = test_peripheral_io_uart_peripheral_uart_close_n();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_close_n");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p1");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p2");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p3");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p4();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p4");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p5();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p5");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p6();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p6");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p7();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p7");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p8();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p8");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p9();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p9");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p10();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p10");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p11();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p11");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p12();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p12");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p13();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p13");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p14();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p14");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p15();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p15");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p16();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p16");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p17();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p17");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_p18();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_p18");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_n1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_n1");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_n2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_n2");
	ret = test_peripheral_io_uart_peripheral_uart_set_baud_rate_n3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_baud_rate_n3");
	ret = test_peripheral_io_uart_peripheral_uart_set_byte_size_p1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_byte_size_p1");
	ret = test_peripheral_io_uart_peripheral_uart_set_byte_size_p2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_byte_size_p2");
	ret = test_peripheral_io_uart_peripheral_uart_set_byte_size_p3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_byte_size_p3");
	ret = test_peripheral_io_uart_peripheral_uart_set_byte_size_p4();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_byte_size_p4");
	ret = test_peripheral_io_uart_peripheral_uart_set_byte_size_n1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_byte_size_n1");
	ret = test_peripheral_io_uart_peripheral_uart_set_byte_size_n2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_byte_size_n2");
	ret = test_peripheral_io_uart_peripheral_uart_set_byte_size_n3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_byte_size_n3");
	ret = test_peripheral_io_uart_peripheral_uart_set_parity_p1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_parity_p1");
	ret = test_peripheral_io_uart_peripheral_uart_set_parity_p2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_parity_p2");
	ret = test_peripheral_io_uart_peripheral_uart_set_parity_p3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_parity_p3");
	ret = test_peripheral_io_uart_peripheral_uart_set_parity_n1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_parity_n1");
	ret = test_peripheral_io_uart_peripheral_uart_set_parity_n2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_parity_n2");
	ret = test_peripheral_io_uart_peripheral_uart_set_parity_n3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_parity_n3");
	ret = test_peripheral_io_uart_peripheral_uart_set_stop_bits_p1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_stop_bits_p1");
	ret = test_peripheral_io_uart_peripheral_uart_set_stop_bits_p2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_stop_bits_p2");
	ret = test_peripheral_io_uart_peripheral_uart_set_stop_bits_n1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_stop_bits_n1");
	ret = test_peripheral_io_uart_peripheral_uart_set_stop_bits_n2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_stop_bits_n2");
	ret = test_peripheral_io_uart_peripheral_uart_set_stop_bits_n3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_stop_bits_n3");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_p1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_p1");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_p2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_p2");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_p3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_p3");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_p4();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_p4");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_n1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_n1");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_n2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_n2");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_n3();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_n3");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_n4();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_n4");
	ret = test_peripheral_io_uart_peripheral_uart_set_flow_control_n5();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_set_flow_control_n5");
	ret = test_peripheral_io_uart_peripheral_uart_read_p();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_read_p");
	ret = test_peripheral_io_uart_peripheral_uart_read_n1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_read_n1");
	ret = test_peripheral_io_uart_peripheral_uart_read_n2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_read_n2");
	ret = test_peripheral_io_uart_peripheral_uart_write_p();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_write_p");
	ret = test_peripheral_io_uart_peripheral_uart_write_n1();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_write_n1");
	ret = test_peripheral_io_uart_peripheral_uart_write_n2();
	__error_check(ret, "test_peripheral_io_uart_peripheral_uart_write_n2");
}

static void __test_peripheral_spi_run()
{
	int ret = PERIPHERAL_ERROR_NONE;

	ret = test_peripheral_io_spi_peripheral_spi_open_p();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_open_p");
	ret = test_peripheral_io_spi_peripheral_spi_open_n1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_open_n1");
	ret = test_peripheral_io_spi_peripheral_spi_open_n2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_open_n2");
	ret = test_peripheral_io_spi_peripheral_spi_open_n3();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_open_n3");
	ret = test_peripheral_io_spi_peripheral_spi_close_p();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_close_p");
	ret = test_peripheral_io_spi_peripheral_spi_close_n();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_close_n");
	ret = test_peripheral_io_spi_peripheral_spi_set_mode_p1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_mode_p1");
	ret = test_peripheral_io_spi_peripheral_spi_set_mode_p2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_mode_p2");
	ret = test_peripheral_io_spi_peripheral_spi_set_mode_p3();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_mode_p3");
	ret = test_peripheral_io_spi_peripheral_spi_set_mode_p4();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_mode_p4");
	ret = test_peripheral_io_spi_peripheral_spi_set_mode_n1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_mode_n1");
	ret = test_peripheral_io_spi_peripheral_spi_set_mode_n2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_mode_n2");
	ret = test_peripheral_io_spi_peripheral_spi_set_mode_n3();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_mode_n3");
	ret = test_peripheral_io_spi_peripheral_spi_set_bit_order_p1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_bit_order_p1");
	ret = test_peripheral_io_spi_peripheral_spi_set_bit_order_p2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_bit_order_p2");
	ret = test_peripheral_io_spi_peripheral_spi_set_bit_order_n1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_bit_order_n1");
	ret = test_peripheral_io_spi_peripheral_spi_set_bit_order_n2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_bit_order_n2");
	ret = test_peripheral_io_spi_peripheral_spi_set_bit_order_n3();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_bit_order_n3");
	ret = test_peripheral_io_spi_peripheral_spi_set_bits_per_word_p();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_bits_per_word_p");
	ret = test_peripheral_io_spi_peripheral_spi_set_bits_per_word_n1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_bits_per_word_n1");
	ret = test_peripheral_io_spi_peripheral_spi_set_bits_per_word_n2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_bits_per_word_n2");
	ret = test_peripheral_io_spi_peripheral_spi_set_frequency_p();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_frequency_p");
	ret = test_peripheral_io_spi_peripheral_spi_set_frequency_n();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_set_frequency_n");
	ret = test_peripheral_io_spi_peripheral_spi_read_p();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_read_p");
	ret = test_peripheral_io_spi_peripheral_spi_read_n1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_read_n1");
	ret = test_peripheral_io_spi_peripheral_spi_read_n2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_read_n2");
	ret = test_peripheral_io_spi_peripheral_spi_write_p();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_write_p");
	ret = test_peripheral_io_spi_peripheral_spi_write_n1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_write_n1");
	ret = test_peripheral_io_spi_peripheral_spi_write_n2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_write_n2");
	ret = test_peripheral_io_spi_peripheral_spi_transfer_p();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_transfer_p");
	ret = test_peripheral_io_spi_peripheral_spi_transfer_n1();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_transfer_n1");
	ret = test_peripheral_io_spi_peripheral_spi_transfer_n2();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_transfer_n2");
	ret = test_peripheral_io_spi_peripheral_spi_transfer_n3();
	__error_check(ret, "test_peripheral_io_spi_peripheral_spi_transfer_n3");
}

int main(int argc, char **argv)
{
	int ret;

	int menu;

	printf("\n\n\n*** Peripheral-IO API Test (UTC) ***");

	while (1) {

		printf("\n\n*************************************************************************\n");
		printf("*                                                                       *\n");
		printf("*    MENU: 1.All  2.GPIO  3.I2C  4.PWM  5.ADC  6.UART  7.SPI  8.Exit    *\n");
		printf("*                                                                       *\n");
		printf("*************************************************************************\n");
		printf("     Input Menu : ");

		if (scanf("%d", &menu) < 0) return -1;

		printf("\n\n");

		fail_count = 0;
		pass_count = 0;

		ret = __test_peripheral_init();
		if (ret != PERIPHERAL_ERROR_NONE) {
			printf("[Message] Failed test init...\n\n");
			return -1;
		}

		switch (menu) {
		case 1:
			__test_peripheral_gpio_run();
			__test_peripheral_i2c_run();
			__test_peripheral_pwm_run();
			__test_peripheral_adc_run();
			__test_peripheral_uart_run();
			break;
		case 2:
			__test_peripheral_gpio_run();
			break;
		case 3:
			__test_peripheral_i2c_run();
			break;
		case 4:
			__test_peripheral_pwm_run();
			break;
		case 5:
			__test_peripheral_adc_run();
			break;
		case 6:
			__test_peripheral_uart_run();
			break;
		case 7:
			__test_peripheral_spi_run();
			break;
		case 8:
			printf("[Message] Close the Peripheral-IO API local Test...\n\n");
			return 0;
		default:
			printf("[Message] Input is wrong...\n\n");
			return -1;
		}

		printf("\n\nTotal : %d, Pass : %d, Fail : %d\n", pass_count + fail_count, pass_count, fail_count);

	}

	return -1;
}
