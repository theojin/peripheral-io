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
#include "test_peripheral_gpio.h"

#define GPIO_PIN_RPI3 26
#define GPIO_PIN_ARTIK530 128
#if defined(SDTA7D)
#define GPIO_PIN_SDTA7D 128
#endif
#define GPIO_PIN_INVALID -99

static bool g_feature = false;
static int pin;

int test_peripheral_io_gpio_initialize(char *model, bool feature)
{
	g_feature = feature;

	if (!strcmp(model, "rpi3"))
		pin = GPIO_PIN_RPI3;
	else if (!strcmp(model, "artik"))
		pin = GPIO_PIN_ARTIK530;
#if defined(SDTA7D)
	else if (!strcmp(model, "sdta7d"))
		pin = GPIO_PIN_SDTA7D;
#endif
	else
		return PERIPHERAL_ERROR_NO_DEVICE;
	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_open_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_open_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_gpio_open(pin, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_open_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_open(GPIO_PIN_INVALID, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(GPIO_PIN_INVALID, &gpio_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_close_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_close_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_gpio_close(NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_close(NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_direction_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_direction_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_HIGH);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_HIGH);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_direction_p3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_direction_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_gpio_set_direction(NULL, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_HIGH);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_set_direction(NULL, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_HIGH);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_direction_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_direction_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_NONE);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_NONE);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_RISING);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_RISING);
		if (ret != PERIPHERAL_ERROR_NONE && ret != PERIPHERAL_ERROR_TRY_AGAIN) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_FALLING);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_FALLING);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_p4(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_BOTH);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_BOTH);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_gpio_set_edge_mode(NULL, PERIPHERAL_GPIO_EDGE_RISING);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_set_edge_mode(NULL, PERIPHERAL_GPIO_EDGE_RISING);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_NONE - 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_NONE - 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_edge_mode_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_BOTH + 1);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_BOTH + 1);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

static void gpio_interrupted_cb(peripheral_gpio_h gpio_h, peripheral_error_e error, void *user_data)
{
	// interrupted callback
}

int test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_p(void)
{
	// see the gpio_interrupted_cb();

	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_interrupted_cb(gpio_h, gpio_interrupted_cb, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_set_edge_mode(gpio_h, PERIPHERAL_GPIO_EDGE_RISING);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_set_interrupted_cb(gpio_h, gpio_interrupted_cb, NULL);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_unset_interrupted_cb(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_gpio_set_interrupted_cb(NULL, gpio_interrupted_cb, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_set_interrupted_cb(NULL, gpio_interrupted_cb, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_set_interrupted_cb_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_set_interrupted_cb(gpio_h, NULL, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_interrupted_cb(gpio_h, NULL, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_p1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_unset_interrupted_cb(gpio_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_interrupted_cb(gpio_h, gpio_interrupted_cb, NULL);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_unset_interrupted_cb(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_p2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_unset_interrupted_cb(gpio_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_unset_interrupted_cb(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_unset_interrupted_cb_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_gpio_unset_interrupted_cb(NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_unset_interrupted_cb(NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_read_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	uint32_t value;

	if (g_feature == false) {
		ret = peripheral_gpio_read(gpio_h, &value);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_read(gpio_h, &value);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_read_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint32_t value;

	if (g_feature == false) {
		ret = peripheral_gpio_read(NULL, &value);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_read(NULL, &value);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_read_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	if (g_feature == false) {
		ret = peripheral_gpio_read(gpio_h, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_read(gpio_h, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_write_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	uint32_t value = 1;

	if (g_feature == false) {
		ret = peripheral_gpio_write(gpio_h, value);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_write(gpio_h, value);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_write_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint32_t value = 1;

	if (g_feature == false) {
		ret = peripheral_gpio_write(NULL, value);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_write(NULL, value);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_gpio_peripheral_gpio_write_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_gpio_h gpio_h = NULL;

	uint32_t value = 2;

	if (g_feature == false) {
		ret = peripheral_gpio_write(gpio_h, value);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_gpio_open(pin, &gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_gpio_set_direction(gpio_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_write(gpio_h, value);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_gpio_close(gpio_h);
			return ret;
		}

		ret = peripheral_gpio_close(gpio_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}
