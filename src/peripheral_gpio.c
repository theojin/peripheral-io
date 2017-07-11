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
#include <assert.h>

#include "peripheral_io.h"
#include "peripheral_gdbus_gpio.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"
#include "peripheral_io_gdbus.h"

typedef struct {
	int pin;
	gpio_isr_cb callback;
	void *user_data;
} gpio_isr_data_s;

static GList *gpio_isr_list = NULL;

int peripheral_gpio_isr_callback(int pin, int value, unsigned long long timestamp)
{
	GList *link;
	gpio_isr_data_s *isr_data;
	gpio_isr_cb_s cb_data;

	link = gpio_isr_list;
	while (link) {
		isr_data = (gpio_isr_data_s*)link->data;

		if (isr_data->pin == pin) {
			cb_data.pin = pin;
			cb_data.value = value;
			cb_data.timestamp = timestamp;
			if (isr_data->callback)
				isr_data->callback(&cb_data, isr_data->user_data);
			return PERIPHERAL_ERROR_NONE;
		}
		link = g_list_next(link);
	}

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_gpio_isr_set(int pin, gpio_isr_cb callback, void *user_data)
{
	GList *link;
	gpio_isr_data_s *isr_data = NULL;

	link = gpio_isr_list;
	while (link) {
		gpio_isr_data_s *tmp;
		tmp = (gpio_isr_data_s*)link->data;
		if (tmp->pin == pin) {
			isr_data = tmp;
			break;
		}
		link = g_list_next(link);
	}

	if (isr_data == NULL) {
		isr_data = (gpio_isr_data_s*)calloc(1, sizeof(gpio_isr_data_s));
		if (isr_data == NULL) {
			_E("failed to allocate gpio_isr_data_s");
			return PERIPHERAL_ERROR_OUT_OF_MEMORY;
		}

		gpio_isr_list = g_list_append(gpio_isr_list, isr_data);
	}

	isr_data->pin = pin;
	isr_data->callback = callback;
	isr_data->user_data = user_data;

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_gpio_isr_unset(int pin)
{
	GList *link;
	gpio_isr_data_s *isr_data;

	link = gpio_isr_list;
	while (link) {
		isr_data = (gpio_isr_data_s*)link->data;

		if (isr_data->pin == pin) {
			gpio_isr_list = g_list_remove_link(gpio_isr_list, link);
			free(link->data);
			g_list_free(link);
			break;
		}
		link = g_list_next(link);
	}

	return PERIPHERAL_ERROR_NONE;
}

/**
 * @brief Initializes(export) gpio pin and creates gpio handle.
 */
int peripheral_gpio_open(int gpio_pin, peripheral_gpio_h *gpio)
{
	int ret = PERIPHERAL_ERROR_NONE;
	peripheral_gpio_h handle;

	RETVM_IF(gpio_pin < 0, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid gpio pin number");

	/* Initialize */
	handle = (peripheral_gpio_h)calloc(1, sizeof(struct _peripheral_gpio_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_gpio_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}
	handle->pin = gpio_pin;

	gpio_proxy_init();

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

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	/* call gpio_close */
	ret = peripheral_gdbus_gpio_close(gpio);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to close the gpio pin, ret : %d", ret);
	gpio_proxy_deinit();

	free(gpio);
	gpio = NULL;

	return ret;
}

/**
 * @brief Gets direction of the gpio.
 */
int peripheral_gpio_get_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e *direction)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	ret = peripheral_gdbus_gpio_get_direction(gpio, direction);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get direction of the gpio pin, ret : %d", ret);

	return ret;
}


/**
 * @brief Sets direction of the gpio pin.
 */
int peripheral_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF(direction > PERIPHERAL_GPIO_DIRECTION_OUT_HIGH, PERIPHERAL_ERROR_INVALID_PARAMETER,
		"Invalid direction input");

	/* call gpio_set_direction */
	ret = peripheral_gdbus_gpio_set_direction(gpio, direction);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set gpio direction, ret : %d", ret);

	return ret;
}

/**
 * @brief Reads value of the gpio.
 */
int peripheral_gpio_read(peripheral_gpio_h gpio, int *value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	/* call gpio_read */
	ret = peripheral_gdbus_gpio_read(gpio, value);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to read value of the gpio pin, ret : %d", ret);

	return ret;
}

/**
 * @brief Writes value to the gpio.
 */
int peripheral_gpio_write(peripheral_gpio_h gpio, int value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	/* call gpio_write */
	ret = peripheral_gdbus_gpio_write(gpio, value);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to write to the gpio pin, ret : %d", ret);

	return ret;
}

/**
 * @brief Gets the edge mode of the gpio.
 */
int peripheral_gpio_get_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e *edge)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	ret = peripheral_gdbus_gpio_get_edge_mode(gpio, edge);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to get edge mode of the gpio pin, ret : %d", ret);

	return ret;
}

/**
 * @brief Sets the edge mode of the gpio pin.
 */
int peripheral_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF(edge > PERIPHERAL_GPIO_EDGE_BOTH, PERIPHERAL_ERROR_INVALID_PARAMETER,
		"Invalid edge input");

	/* call gpio_set_edge_mode */
	ret = peripheral_gdbus_gpio_set_edge_mode(gpio, edge);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set edge mode of the gpio pin, ret : %d", ret);

	return ret;
}

/**
 * @brief Registers a callback function to be invoked when the gpio interrupt is triggered.
 */
int peripheral_gpio_register_cb(peripheral_gpio_h gpio, gpio_isr_cb callback, void *user_data)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	ret = peripheral_gdbus_gpio_register_cb(gpio, callback, user_data);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to register cb, ret : %d", ret);
		return ret;
	}

	/* set isr */
	ret = peripheral_gpio_isr_set(gpio->pin, callback, user_data);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to register gpio isr, ret : %d", ret);

	return ret;
}

/**
 * @brief Unregisters the callback function for the gpio handler.
 */
int peripheral_gpio_unregister_cb(peripheral_gpio_h gpio)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	ret = peripheral_gdbus_gpio_unregister_cb(gpio);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to unregister gpio isr, ret : %d", ret);
		return ret;
	}

	/* clean up isr */
	ret = peripheral_gpio_isr_unset(gpio->pin);

	return ret;
}

/**
 * @brief Gets pin number of the gpio handle.
 */
int peripheral_gpio_get_pin(peripheral_gpio_h gpio, int *gpio_pin)
{
	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	*gpio_pin = gpio->pin;

	return PERIPHERAL_ERROR_NONE;
}
