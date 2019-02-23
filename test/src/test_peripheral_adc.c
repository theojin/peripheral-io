/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
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
#include "test_peripheral_adc.h"

#define ADC_DEVICE_ARTIK530 0
#if defined(SDTA7D)
#define ADC_DEVICE_SDTA7D 0
#endif
#define ADC_DEVICE_INVALID -99
#define ADC_CHANNEL 3
#define ADC_CHANNEL_INVALID -99

static bool g_feature = true;
static int device;
static int channel;

int test_peripheral_io_adc_initialize(char *model, bool feature)
{
	g_feature = feature;

	if (!strcmp(model, "artik"))
		device = ADC_DEVICE_ARTIK530;
#if defined(SDTA7D)
	else if (!strcmp(model, "sdta7d"))
		device = ADC_DEVICE_SDTA7D;
#endif
	else
		return PERIPHERAL_ERROR_NO_DEVICE;

	channel = ADC_CHANNEL;

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_open_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_adc_h adc_h = NULL;

	if (g_feature == false) {
		ret = peripheral_adc_open(device, channel, &adc_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_open(device, channel, &adc_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_adc_close(adc_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_open_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_adc_open(device, channel, NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_open(device, channel, NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_open_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_adc_h adc_h = NULL;

	if (g_feature == false) {
		ret = peripheral_adc_open(ADC_DEVICE_INVALID, channel, &adc_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_open(ADC_DEVICE_INVALID, channel, &adc_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_open_n3(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_adc_h adc_h = NULL;

	if (g_feature == false) {
		ret = peripheral_adc_open(device, ADC_CHANNEL_INVALID, &adc_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_open(device, ADC_CHANNEL_INVALID, &adc_h);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_close_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_adc_h adc_h = NULL;

	if (g_feature == false) {
		ret = peripheral_adc_close(adc_h);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_open(device, channel, &adc_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_adc_close(adc_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_close_n(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (g_feature == false) {
		ret = peripheral_adc_close(NULL);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_close(NULL);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_read_p(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_adc_h adc_h = NULL;

	uint32_t value;

	if (g_feature == false) {
		ret = peripheral_adc_read(adc_h, &value);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_open(device, channel, &adc_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_adc_read(adc_h, &value);
		if (ret != PERIPHERAL_ERROR_NONE) {
			peripheral_adc_close(adc_h);
			return ret;
		}

		ret = peripheral_adc_close(adc_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_read_n1(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	uint32_t value;

	if (g_feature == false) {
		ret = peripheral_adc_read(NULL, &value);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_read(NULL, &value);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}

int test_peripheral_io_adc_peripheral_adc_read_n2(void)
{
	int ret = PERIPHERAL_ERROR_NONE;

	peripheral_adc_h adc_h = NULL;

	uint32_t value;

	if (g_feature == false) {
		ret = peripheral_adc_read(adc_h, &value);
		if (ret != PERIPHERAL_ERROR_NOT_SUPPORTED)
			return ret;

	} else {
		ret = peripheral_adc_open(device, channel, &adc_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;

		ret = peripheral_adc_read(adc_h, &value);
		if (ret != PERIPHERAL_ERROR_INVALID_PARAMETER) {
			peripheral_adc_close(adc_h);
			return ret;
		}

		ret = peripheral_adc_close(adc_h);
		if (ret != PERIPHERAL_ERROR_NONE)
			return ret;
	}

	return PERIPHERAL_ERROR_NONE;
}
