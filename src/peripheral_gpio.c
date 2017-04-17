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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes gpio_context, based on Gpio pin.
 */

#define GPIO_NAME	"gpio"

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

	if (!get_dbus_connection()) {
		ret = set_dbus_connection();
		if (ret != PERIPHERAL_ERROR_NONE)
			goto exit;
	}

	ret = peripheral_dbus_gpio(handle, GPIO_NAME, "OPEN", 0 , 0);

exit:
	if (ret != PERIPHERAL_ERROR_NONE) {
		free(handle);
		handle = NULL;
	}

	*gpio = handle;

	return ret;
}

/**
 * @brief Closes the gpio_context.
 */
int peripheral_gpio_close(peripheral_gpio_h gpio)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	/* call gpio_close */
	ret = peripheral_dbus_gpio(gpio, GPIO_NAME, "CLOSE", 0 , 0);
	if (ret)
		ret = TIZEN_ERROR_IO_ERROR;

	free(gpio);
	gpio = NULL;

	return ret;
}

/**
 * @brief Sets Gpio direction.
 */
int peripheral_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	if (direction > PERIPHERAL_GPIO_DIRECTION_OUT_HIGH) {
		ret = PERIPHERAL_ERROR_INVALID_PARAMETER;
	} else {
		if (gpio->direction != direction) {
			gpio->direction = direction;
			ret = peripheral_dbus_gpio(gpio, GPIO_NAME, "SET_DIR", 0 , 0);
		}
	}
	/* call gpio_set_direction */

	return ret;
}

/**
 * @brief Sets the edge mode on the Gpio.
 */
int peripheral_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	if (edge > PERIPHERAL_GPIO_EDGE_FALLING) {
		ret = PERIPHERAL_ERROR_INVALID_PARAMETER;
	} else {
		if (gpio->edge != edge) {
			gpio->edge = edge;
			ret = peripheral_dbus_gpio(gpio, GPIO_NAME, "SET_EDGE", 0 , 0);
		}
	}
	/* call gpio_set_edge_mode */

	return ret;
}

/**
 * @brief Registers event handler callback for interrupt.
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
 * @brief Unregisters event handler callback for interrupt.
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
 * @brief Reads the gpio value.
 */
int peripheral_gpio_read(peripheral_gpio_h gpio, int *val)
{
	int value = 0;
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	/* call gpio_read */
	ret = peripheral_dbus_gpio(gpio, GPIO_NAME, "READ", 0, &value);
	*val = value;

	return ret;
}

/**
 * @brief Writes to the gpio value.
 */
int peripheral_gpio_write(peripheral_gpio_h gpio, int value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_dbus_gpio(gpio, GPIO_NAME, "WRITE", value , 0);
	/* call gpio_write */

	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	return ret;
}

/**
 * @brief Gets a direction of the Gpio.
 */
int peripheral_gpio_get_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e *direction)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_dbus_gpio(gpio, GPIO_NAME, "GET_DIR", 0 , 0);

	if (ret == PERIPHERAL_ERROR_NONE)
		(*direction) = gpio->direction;

	return ret;
}

/**
 * @brief Gets a pin number of the Gpio.
 */
int peripheral_gpio_get_pin(peripheral_gpio_h gpio, int *gpio_pin)
{
	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	*gpio_pin = gpio->pin;

	return PERIPHERAL_ERROR_NONE;
}

/**
 * @brief Gets a edge mode of the Gpio.
 */
int peripheral_gpio_get_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e *edge)
{
	int ret = PERIPHERAL_ERROR_NONE;

	/* check validation of gpio context handle */
	if (gpio == NULL)
		return PERIPHERAL_ERROR_INVALID_PARAMETER;

	ret = peripheral_dbus_gpio(gpio, GPIO_NAME, "GET_EDGE", 0 , 0);

	if (ret == PERIPHERAL_ERROR_NONE)
		(*edge) = gpio->edge;

	return ret;
}

#ifdef __cplusplus
}
#endif
