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
#include "peripheral_dbus.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"
#include "peripheral_io_gdbus.h"

/**
 * @brief Initializes(export) gpio pin and creates gpio handle.
 */
int peripheral_gpio_open(int gpio_pin, peripheral_gpio_h *gpio)
{
	int ret = PERIPHERAL_ERROR_NONE;
	peripheral_gpio_h handle;

	assert(gpio_pin >= 0);

	/* Initialize */
	handle = (peripheral_gpio_h)calloc(1, sizeof(struct _peripheral_gpio_s));

	if (handle == NULL) {
		_E("Failed to allocate peripheral_gpio_h");
		return PERIPHERAL_ERROR_OUT_OF_MEMORY;
	}
	handle->pin = gpio_pin;

	gpio_proxy_init();

	ret = peripheral_dbus_gpio_open(handle);

	if (ret != PERIPHERAL_ERROR_NONE) {
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

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	/* call gpio_close */
	ret = peripheral_dbus_gpio_close(gpio);
	if (ret)
		ret = TIZEN_ERROR_IO_ERROR;
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

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_dbus_gpio_get_direction(gpio, direction);
	if (ret == PERIPHERAL_ERROR_NONE)
		gpio->direction = (*direction);

	return ret;
}


/**
 * @brief Sets direction of the gpio pin.
 */
int peripheral_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	if (direction > PERIPHERAL_GPIO_DIRECTION_OUT_HIGH)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	/* call gpio_set_direction */
	ret = peripheral_dbus_gpio_set_direction(gpio, direction);
	if (ret == PERIPHERAL_ERROR_NONE)
		gpio->direction = direction;

	return ret;
}

/**
 * @brief Reads value of the gpio.
 */
int peripheral_gpio_read(peripheral_gpio_h gpio, int *value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	/* call gpio_read */
	ret = peripheral_dbus_gpio_read(gpio, value);

	return ret;
}

/**
 * @brief Writes value to the gpio.
 */
int peripheral_gpio_write(peripheral_gpio_h gpio, int value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	/* call gpio_write */
	ret = peripheral_dbus_gpio_write(gpio, value);

	return ret;
}

/**
 * @brief Gets the edge mode of the gpio.
 */
int peripheral_gpio_get_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e *edge)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_dbus_gpio_get_edge_mode(gpio, edge);
	if (ret == PERIPHERAL_ERROR_NONE)
		gpio->edge = (*edge);

	return ret;
}

/**
 * @brief Sets the edge mode of the gpio pin.
 */
int peripheral_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	if (edge > PERIPHERAL_GPIO_EDGE_BOTH)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	/* call gpio_set_edge_mode */
	ret = peripheral_dbus_gpio_set_edge_mode(gpio, edge);
	if (ret == PERIPHERAL_ERROR_NONE)
		gpio->edge = edge;

	return ret;
}

/**
 * @brief Registers a callback function to be invoked when the gpio interrupt is triggered.
 */
int peripheral_gpio_register_cb(peripheral_gpio_h gpio, gpio_isr_cb callback, void *user_data)
{
	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	//TODO
	return PERIPHERAL_ERROR_INVALID_OPERATION;
}

/**
 * @brief Unregisters the callback function for the gpio handler.
 */
int peripheral_gpio_unregister_cb(peripheral_gpio_h gpio)
{
	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;
	//TODO
	return PERIPHERAL_ERROR_INVALID_OPERATION;
}

/**
 * @brief Gets pin number of the gpio handle.
 */
int peripheral_gpio_get_pin(peripheral_gpio_h gpio, int *gpio_pin)
{
	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	*gpio_pin = gpio->pin;

	return PERIPHERAL_ERROR_NONE;
}
