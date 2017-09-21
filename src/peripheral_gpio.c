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
	peripheral_gpio_h handle;
	peripheral_gpio_interrupted_cb callback;
	void *user_data;
} interrupted_cb_info_s;

static GList *interrupted_cb_info_list = NULL;

int peripheral_gpio_interrupted_cb_handler(int pin, int value, unsigned long long timestamp, int error)
{
	GList *link;
	interrupted_cb_info_s *cb_info;

	link = interrupted_cb_info_list;
	while (link) {
		cb_info = (interrupted_cb_info_s*)link->data;
		if (cb_info->handle->pin == pin) {
			if (cb_info->callback)
				cb_info->callback(cb_info->handle, error, cb_info->user_data);
			return PERIPHERAL_ERROR_NONE;
		}
		link = g_list_next(link);
	}

	return PERIPHERAL_ERROR_NONE;
}

static int __interrupted_cb_info_list_append(peripheral_gpio_h gpio, peripheral_gpio_interrupted_cb callback, void *user_data)
{
	GList *link;
	interrupted_cb_info_s *cb_info = NULL;

	link = interrupted_cb_info_list;
	while (link) {
		interrupted_cb_info_s *tmp;
		tmp = (interrupted_cb_info_s*)link->data;
		if (tmp->handle == gpio) {
			cb_info = tmp;
			break;
		}
		link = g_list_next(link);
	}

	if (cb_info == NULL) {
		cb_info = (interrupted_cb_info_s*)calloc(1, sizeof(interrupted_cb_info_s));
		if (cb_info == NULL) {
			_E("failed to allocate interrupted_cb_info_s");
			return PERIPHERAL_ERROR_OUT_OF_MEMORY;
		}

		link = g_list_append(link, cb_info);
	}

	cb_info->handle = gpio;
	cb_info->callback = callback;
	cb_info->user_data = user_data;

	return PERIPHERAL_ERROR_NONE;
}

static int __interrupted_cb_info_list_remove(peripheral_gpio_h gpio)
{
	GList *link;
	interrupted_cb_info_s *cb_info;

	link = interrupted_cb_info_list;
	while (link) {
		cb_info = (interrupted_cb_info_s*)link->data;

		if (cb_info->handle == gpio) {
			interrupted_cb_info_list = g_list_remove_link(interrupted_cb_info_list, link);
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

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid gpio handle");
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
 * @brief Sets direction of the gpio pin.
 */
int peripheral_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF((direction < PERIPHERAL_GPIO_DIRECTION_IN) || (direction > PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW), PERIPHERAL_ERROR_INVALID_PARAMETER, "Invalid direction input");

	/* call gpio_set_direction */
	ret = peripheral_gdbus_gpio_set_direction(gpio, direction);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set gpio direction, ret : %d", ret);

	return ret;
}


/**
 * @brief Sets the edge mode of the gpio pin.
 */
int peripheral_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF((edge < PERIPHERAL_GPIO_EDGE_NONE) || (edge > PERIPHERAL_GPIO_EDGE_BOTH), PERIPHERAL_ERROR_INVALID_PARAMETER, "edge input is invalid");

	/* call gpio_set_edge_mode */
	ret = peripheral_gdbus_gpio_set_edge_mode(gpio, edge);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to set edge mode of the gpio pin, ret : %d", ret);

	return ret;
}

/**
 * @brief Registers a callback function to be invoked when the gpio interrupt is triggered.
 */
int peripheral_gpio_set_interrupted_cb(peripheral_gpio_h gpio, peripheral_gpio_interrupted_cb callback, void *user_data)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF(callback == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio interrupted callback is NULL");

	ret = peripheral_gdbus_gpio_set_interrupted_cb(gpio, callback, user_data);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to set gpio interrupted cb, ret : %d", ret);
		return ret;
	}

	/* set isr */
	ret = __interrupted_cb_info_list_append(gpio, callback, user_data);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to append gpio interrupt callback info, ret : %d", ret);

	return ret;
}

/**
 * @brief Unregisters the callback function for the gpio handler.
 */
int peripheral_gpio_unset_interrupted_cb(peripheral_gpio_h gpio)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");

	ret = peripheral_gdbus_gpio_unset_interrupted_cb(gpio);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("Failed to unset gpio interrupt callback, ret : %d", ret);
		return ret;
	}

	ret = __interrupted_cb_info_list_remove(gpio);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to remove gpio interrupt callback info, ret : %d", ret);

	return ret;
}

/**
 * @brief Reads value of the gpio.
 */
int peripheral_gpio_read(peripheral_gpio_h gpio, uint32_t *value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF(value == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio read value is invalid");

	/* call gpio_read */
	ret = peripheral_gdbus_gpio_read(gpio, (int *)value);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to read value of the gpio pin, ret : %d", ret);

	return ret;
}

/**
 * @brief Writes value to the gpio.
 */
int peripheral_gpio_write(peripheral_gpio_h gpio, uint32_t value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	RETVM_IF(gpio == NULL, PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio handle is NULL");
	RETVM_IF((value != 0) && (value != 1), PERIPHERAL_ERROR_INVALID_PARAMETER, "gpio value is invalid");

	/* call gpio_write */
	ret = peripheral_gdbus_gpio_write(gpio, (int)value);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to write to the gpio pin, ret : %d", ret);

	return ret;
}
