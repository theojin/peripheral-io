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
#include "peripheral_gdbus_gpio.h"
#include "peripheral_common.h"
#include "peripheral_handle.h"

#define PERIPHERAL_IO_GPIO_FEATURE "http://tizen.org/feature/peripheral_io.gpio"

#define GPIO_FEATURE_UNKNOWN -1
#define GPIO_FEATURE_FALSE    0
#define GPIO_FEATURE_TRUE     1

static int gpio_feature = GPIO_FEATURE_UNKNOWN;

static bool __is_feature_supported()
{
	int ret = SYSTEM_INFO_ERROR_NONE;
	bool feature = false;

	if (gpio_feature == GPIO_FEATURE_UNKNOWN) {
		ret = system_info_get_platform_bool(PERIPHERAL_IO_GPIO_FEATURE, &feature);
		RETVM_IF(ret != SYSTEM_INFO_ERROR_NONE, false, "Failed to get system info");

		gpio_feature = (feature ? GPIO_FEATURE_TRUE : GPIO_FEATURE_FALSE);
	}
	return (gpio_feature == GPIO_FEATURE_TRUE ? true : false);
}

/**
 * @brief Initializes(export) gpio pin and creates gpio handle.
 */
int peripheral_gpio_open(int gpio_pin, peripheral_gpio_h *gpio)
{
	int ret = PERIPHERAL_ERROR_NONE;
	peripheral_gpio_h handle;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "GPIO feature is not supported");
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid gpio handle");
	RETVM_IF(gpio_pin < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid gpio pin number");

	/* Initialize */
	handle = (peripheral_gpio_h)calloc(1, sizeof(struct _peripheral_gpio_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_gpio_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}
	handle->pin = gpio_pin;

	ret = peripheral_gdbus_gpio_open(handle);

	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to open the gpio pin, ret : %d", ret);
		free(handle);
		handle = NULL;
	}

	*gpio = handle;

	return ret;
}

/**
 * @brief Closes the gpio_context.
 * @brief Releases the gpio handle and finalize(unexport) the gpio pin.
 */
int peripheral_gpio_close(peripheral_gpio_h gpio)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "GPIO feature is not supported");
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	/* call gpio_close */
	ret = peripheral_gdbus_gpio_close(gpio);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to close the gpio pin, ret : %d", ret);

	free(gpio);
	gpio = NULL;

	return ret;
}

/**
 * @brief Sets direction of the gpio pin.
 */
int peripheral_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "GPIO feature is not supported");
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF((direction < PERIPHERAL_GPIO_DIRECTION_IN) || (direction > PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid direction input");

	/* call gpio_set_direction */
	// TODO : replace interface function

	return ret;
}

/**
 * @brief Sets the edge mode of the gpio pin.
 */
int peripheral_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "GPIO feature is not supported");
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF((edge < PERIPHERAL_GPIO_EDGE_NONE) || (edge > PERIPHERAL_GPIO_EDGE_BOTH), PERIPHERAL_ERROR_INVALID_PARAMETER, "edge input is invalid");

	/* call gpio_set_edge_mode */
	// TODO : replace interface function

	return ret;
}

/**
 * @brief Registers a callback function to be invoked when the gpio interrupt is triggered.
 */
int peripheral_gpio_set_interrupted_cb(peripheral_gpio_h gpio, peripheral_gpio_interrupted_cb callback, void *user_data)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "GPIO feature is not supported");
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF(callback == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio interrupted callback is NULL");

	// TODO : replace interface function

	return ret;
}

/**
 * @brief Unregisters the callback function for the gpio handler.
 */
int peripheral_gpio_unset_interrupted_cb(peripheral_gpio_h gpio)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "GPIO feature is not supported");
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	// TODO : replace interface function

	return ret;
}

/**
 * @brief Reads value of the gpio.
 */
int peripheral_gpio_read(peripheral_gpio_h gpio, uint32_t *value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "GPIO feature is not supported");
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF(value == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio read value is invalid");

	/* call gpio_read */
	// TODO : replace interface function

	return ret;
}

/**
 * @brief Writes value to the gpio.
 */
int peripheral_gpio_write(peripheral_gpio_h gpio, uint32_t value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(__is_feature_supported() == false, PERIPHERAL_ERROR_NOT_SUPPORTED, "GPIO feature is not supported");
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF((value != 0) && (value != 1), PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio value is invalid");

	/* call gpio_write */
	// TODO : replace interface function

	return ret;
}
