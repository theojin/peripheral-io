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

#include <stdlib.h>
#include <system_info.h>

#include "peripheral_io.h"
#include "peripheral_handle.h"
#include "peripheral_gdbus_adc.h"
#include "peripheral_interface_adc.h"
#include "peripheral_log.h"

#define PERIPHERAL_IO_ADC_FEATURE "http://tizen.org/feature/peripheral_io.adc"

#define ADC_FEATURE_UNKNOWN -1
#define ADC_FEATURE_FALSE    0
#define ADC_FEATURE_TRUE     1

static int adc_feature = ADC_FEATURE_UNKNOWN;

static bool __is_feature_supported(void)
{
	int ret = SYSTEM_INFO_ERROR_NONE;
	bool feature = false;

	if (adc_feature == ADC_FEATURE_UNKNOWN) {
		ret = system_info_get_platform_bool(PERIPHERAL_IO_ADC_FEATURE, &feature);
		RETVM_IF(ret != SYSTEM_INFO_ERROR_NONE, false, "Failed to get system info");

		adc_feature = (feature ? ADC_FEATURE_TRUE : ADC_FEATURE_FALSE);
	}
	return (adc_feature == ADC_FEATURE_TRUE ? true : false);
}

/**
 * @brief Initializes adc pin and creates adc handle.
 */
int peripheral_adc_open(int device, int channel, peripheral_adc_h *adc)
{
	int ret = PERIPHERAL_ERROR_NONE;
	peripheral_adc_h handle;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "ADC feature is not supported");
	RETVM_IF(adc == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid adc handle");
	RETVM_IF(device < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid adc device number");
	RETVM_IF(channel < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid adc channel number");

	handle = (peripheral_adc_h)calloc(1, sizeof(struct _peripheral_adc_s));
	if (handle == NULL) {
		_E("Failed to allocate peripheral_adc_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}

	ret = peripheral_gdbus_adc_open(handle, device, channel);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to open the adc pin, ret : %d", ret);
		free(handle);
		handle = NULL;
		return ret;
	}

	*adc = handle;

	return PERIPHERAL_ERROR_NONE;
}

/**
 * @brief Releases the adc handle.
 */
int peripheral_adc_close(peripheral_adc_h adc)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "ADC feature is not supported");
	RETVM_IF(adc == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "adc handle is NULL");

	/* call adc_close */
	ret = peripheral_gdbus_adc_close(adc);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to close the adc pin, ret : %d", ret);

	peripheral_interface_adc_close(adc);

	free(adc);
	adc = NULL;

	return ret;
}

/**
 * @brief Reads value of the adc.
 */
int peripheral_adc_read(peripheral_adc_h adc, uint32_t *value)
{
	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "ADC feature is not supported");
	RETVM_IF(adc == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "adc handle is NULL");
	RETVM_IF(value == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "adc read value is invalid");

	return peripheral_interface_adc_read(adc, value);
}
