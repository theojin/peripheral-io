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

#ifndef __PERIPHERAL_IO_H__
#define __PERIPHERAL_IO_H__

#include <stdint.h>
#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file peripheral_io.h
 * @brief This file contains the peripheral-io API
 */

/**
 * @brief Enumeration for peripheral-io error.
 * @since_tizen
 */
typedef enum {
	PERIPHERAL_ERROR_NONE                = TIZEN_ERROR_NONE,                /**< Successful */
	PERIPHERAL_ERROR_IO_ERROR            = TIZEN_ERROR_IO_ERROR,            /**< I/O error */
	PERIPHERAL_ERROR_OUT_OF_MEMORY       = TIZEN_ERROR_OUT_OF_MEMORY,       /**< Out of memory */
	PERIPHERAL_ERROR_PERMISSON_DENIED    = TIZEN_ERROR_PERMISSION_DENIED,   /**< Permission denied */
	PERIPHERAL_ERROR_RESOURCE_BUSY       = TIZEN_ERROR_RESOURCE_BUSY,       /**< Device or resource busy */
	PERIPHERAL_ERROR_INVALID_PARAMETER   = TIZEN_ERROR_INVALID_PARAMETER,   /**< Invalid parameter */
	PERIPHERAL_ERROR_NO_DATA             = TIZEN_ERROR_NO_DATA,             /**< No data available */
	PERIPHERAL_ERROR_INVALID_OPERATION   = TIZEN_ERROR_INVALID_OPERATION,   /**< Function not implemented */
	PERIPHERAL_ERROR_TIMED_OUT           = TIZEN_ERROR_TIMED_OUT,           /**< Time out */
	PERIPHERAL_ERROR_NOT_SUPPORTED       = TIZEN_ERROR_NOT_SUPPORTED,       /**< Not supported */
	PERIPHERAL_ERROR_UNKNOWN             = TIZEN_ERROR_UNKNOWN,             /**< Unknown error */
	PERIPHERAL_ERROR_NO_DEVICE           = -ENODEV,                         /**< No such device */
} peripheral_error_e;

/**
 * @addtogroup CAPI_SYSTEM_PERPHERAL_GPIO_MODULE
 * @{
 */

/**
 * @brief Enumeration of gpio direction
 */
typedef enum {
	PERIPHERAL_GPIO_DIRECTION_IN = 0,    /**< Input Mode */
	PERIPHERAL_GPIO_DIRECTION_OUT,       /**< Output mode and this implies "low" output value */
	PERIPHERAL_GPIO_DIRECTION_OUT_HIGH,  /**< Output mode and value also be written as "high" */
} peripheral_gpio_direction_e;

/**
 * @brief Enumeration of edge type for gpio interrupt
 */
typedef enum {
	PERIPHERAL_GPIO_EDGE_NONE = 0,  /**< No interrupt on Gpio */
	PERIPHERAL_GPIO_EDGE_RISING,    /**< Interrupt on rising only */
	PERIPHERAL_GPIO_EDGE_FALLING,   /**< Interrupt on falling only */
	PERIPHERAL_GPIO_EDGE_BOTH,      /**< Interrupt on rising & falling */
} peripheral_gpio_edge_e;

/**
 * @brief The handle to the gpio pin
 * @since_tizen 4.0
 */
typedef struct _peripheral_gpio_s* peripheral_gpio_h;

/**
 * @brief Called when the gpio interrupt is triggered.
 * @since_tizen 4.0
 *
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see peripheral_gpio_register_cb()
 * @see peripheral_gpio_unregister_cb()
 */
typedef void(*gpio_isr_cb)(void *user_data);

/**
 * @brief Initilizes(export) gpio pin and creates gpio handle.
 * @since_tizen 4.0
 *
 * @param[in] gpio_pin The gpio pin number what you want to use
 * @param[out] gpio The gpio handle is created on success
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_IO_ERROR I/O operation failed
 * @retval #PERIPHERAL_ERROR_OUT_OF_MEMORY Memory allocation failed
 * @retval #PERIPHERAL_ERROR_PERMISSON_DENIED Permission denied
 * @retval #PERIPHERAL_ERROR_UNKNOWN Unknown internal error
 * @retval #PERIPHERAL_ERROR_NO_DEVICE Device is not exist or removed
 *
 * @see peripheral_gpio_close()
 */
int peripheral_gpio_open(int gpio_pin, peripheral_gpio_h *gpio);

/**
 * @brief Release the gpio handle and finalize(unexport) the gpio pin.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin to release
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_IO_ERROR I/O operation failed
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #PERIPHERAL_ERROR_UNKNOWN Unknown internal error
 * @retval #PERIPHERAL_ERROR_NO_DEVICE Device is not exist or removed
 *
 * @see peripheral_gpio_open()
 */
int peripheral_gpio_close(peripheral_gpio_h gpio);

/**
 * @brief Sets direction of the gpio pin.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin to set
 * @param[in] direction The direction type of the gpio pin
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_IO_ERROR I/O operation failed
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #PERIPHERAL_ERROR_UNKNOWN Unknown internal error
 * @retval #PERIPHERAL_ERROR_NO_DEVICE Device is not exist or removed
 */
int peripheral_gpio_set_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e direction);

/**
 * @brief Sets the edge mode of the gpio pin.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin to set
 * @param[in] edge The edge type of the gpio pin
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_IO_ERROR I/O operation failed
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #PERIPHERAL_ERROR_UNKNOWN Unknown internal error
 * @retval #PERIPHERAL_ERROR_NO_DEVICE Device is not exist or removed
 */
int peripheral_gpio_set_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e edge);

/**
 * @brief Registers a callback function to be invoked when the gpio interrupt is triggered.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin to set
 * @param[in] edge The edge type of the gpio pin
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successfu
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parametera
 *
 * @see peripheral_gpio_set_edge_mode()
 * @see peripheral_gpio_unregister_cb()
 */
int peripheral_gpio_register_cb(peripheral_gpio_h gpio, gpio_isr_cb callback, void *user_data);

/**
 * @brief Unregisters the callback function for the gpio handler.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see peripheral_gpio_register_cb()
 */
int peripheral_gpio_unregister_cb(peripheral_gpio_h gpio);

/**
 * @brief Reads the gpio value.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin
 * @param[out] value The result of the gpio
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_IO_ERROR I/O operation failed
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #PERIPHERAL_ERROR_UNKNOWN Unknown internal error
 * @retval #PERIPHERAL_ERROR_NO_DEVICE Device is not exist or removed
 */
int peripheral_gpio_read(peripheral_gpio_h gpio, int *value);

/**
 * @brief Writes the gpio value.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin
 * @param[in] value The value to be written to the gpio
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_IO_ERROR I/O operation failed
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #PERIPHERAL_ERROR_UNKNOWN Unknown internal error
 * @retval #PERIPHERAL_ERROR_NO_DEVICE Device is not exist or removed
 */
int peripheral_gpio_write(peripheral_gpio_h gpio, int value);

/**
 * @brief Gets direction of the gpio.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin
 * @param[out] value The value to be written to the gpio
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_IO_ERROR I/O operation failed
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #PERIPHERAL_ERROR_UNKNOWN Unknown internal error
 * @retval #PERIPHERAL_ERROR_NO_DEVICE Device is not exist or removed
 */
int peripheral_gpio_get_direction(peripheral_gpio_h gpio, peripheral_gpio_direction_e *direction);

/**
 * @brief Gets pin number of the gpio.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin
 * @param[out] gpio_pin The number of the gpio
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 */
int peripheral_gpio_get_pin(peripheral_gpio_h gpio, int *gpio_pin);

/**
 * @brief Gets edge mode of the gpio.
 * @since_tizen 4.0
 *
 * @param[in] gpio The handle to the gpio pin
 * @param[out] gpio_pin The number of the gpio
 *
 * @return 0 on success, otherwise a negative error value
 * @retval #PERIPHERAL_ERROR_NONE Successful
 * @retval #PERIPHERAL_ERROR_IO_ERROR I/O operation failed
 * @retval #PERIPHERAL_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #PERIPHERAL_ERROR_UNKNOWN Unknown internal error
 * @retval #PERIPHERAL_ERROR_NO_DEVICE Device is not exist or removed
 */
int peripheral_gpio_get_edge_mode(peripheral_gpio_h gpio, peripheral_gpio_edge_e *edge);

/**
* @}
*/

/**
 * @addtogroup CAPI_SYSTEM_PERPHERAL_I2C_MODULE
 * @{
 */

/**
 * @brief Struct for peripheral_gpio_s
 */
struct _peripheral_i2c_s {
	int fd;
};
typedef struct _peripheral_i2c_s *peripheral_i2c_context_h;

peripheral_i2c_context_h peripheral_i2c_init(int bus);

int peripheral_i2c_stop(peripheral_i2c_context_h hnd);

int peripheral_i2c_set_address(peripheral_i2c_context_h hnd, int address);

int peripheral_i2c_read(peripheral_i2c_context_h hnd, uint8_t *data, int length);

int peripheral_i2c_write(peripheral_i2c_context_h hnd, uint8_t *data, int length);


/**
* @}
*/

/**
 * @addtogroup CAPI_SYSTEM_PERPHERAL_PWM_MODULE
 * @{
 */

struct _peripheral_pwm_s {
	int device;
	int channel;
	int period;
	int duty_cycle;
	int enabled;
};
typedef struct _peripheral_pwm_s *peripheral_pwm_context_h;

typedef enum {
	PERIPHERAL_PWM_DISABLE = 0,
	PERIPHERAL_PWM_ENABLE,
} peripheral_pwm_state_e;

peripheral_pwm_context_h peripheral_pwm_open(int device, int channel);

int peripheral_pwm_close(peripheral_pwm_context_h pwm);

int peripheral_pwm_set_duty_cycle(peripheral_pwm_context_h pwm, int duty_cycle);

int peripheral_pwm_set_period(peripheral_pwm_context_h pwm, int period);

int peripheral_pwm_set_enabled(peripheral_pwm_context_h pwm, peripheral_pwm_state_e enable);

int peripheral_pwm_is_enabled(peripheral_pwm_context_h pwm);

int peripheral_pwm_get_duty_cycle(peripheral_pwm_context_h pwm, int *duty_cycle);

int peripheral_pwm_get_period(peripheral_pwm_context_h pwm, int *period);


/**
* @}
*/

/**
 * @addtogroup CAPI_SYSTEM_PERPHERAL_ADC_MODULE
 * @{
 */

/**
 * @brief Struct for peripheral_gpio_s
 */

#define DEVICE_NAME_SIZE	20

struct _peripheral_adc_s {
	char device_name[DEVICE_NAME_SIZE];
	int channel;
};

/**
 * @brief Pointer definition to the internal struct peripheral_adc_s
 */
typedef struct _peripheral_adc_s* peripheral_adc_context_h;

peripheral_adc_context_h peripheral_adc_open(int channel);

int peripheral_adc_read(peripheral_adc_context_h dev, int *data);

int peripheral_adc_close(peripheral_adc_context_h dev);

/**
* @}
*/

/**
 * @addtogroup CAPI_SYSTEM_PERPHERAL_UART_MODULE
 * @{
 */
struct _peripheral_uart_s {
	int fd;
};


typedef struct _peripheral_uart_s* peripheral_uart_context_h;

typedef enum {
	PERIPHERAL_UART_PARITY_NONE = 0,
	PERIPHERAL_UART_PARITY_EVEN,
	PERIPHERAL_UART_PARITY_ODD,
} peripheral_uart_parity_e;

peripheral_uart_context_h peripheral_uart_init(const char *path);

int peripheral_uart_stop(peripheral_uart_context_h hnd);

int peripheral_uart_flush(peripheral_uart_context_h hnd);

int peripheral_uart_set_baudrate(peripheral_uart_context_h hnd, unsigned int baud);

int peripheral_uart_set_mode(peripheral_uart_context_h hnd, int bytesize, peripheral_uart_parity_e parity, int stopbits);

int peripheral_uart_set_flowcontrol(peripheral_uart_context_h hnd, int xonxoff, int rtscts);

int peripheral_uart_read(peripheral_uart_context_h hnd, char *buf, unsigned int length);

int peripheral_uart_write(peripheral_uart_context_h hnd, const char *buf, unsigned int length);

/**
* @}
*/

/**
 * @addtogroup CAPI_SYSTEM_PERPHERAL_SPI_MODULE
 * @{
 */

typedef enum {
	PERIPHERAL_SPI_MODE0 = 0,
	PERIPHERAL_SPI_MODE1,
	PERIPHERAL_SPI_MODE2,
	PERIPHERAL_SPI_MODE3
} peripheral_spi_mode_e;

struct peripheral_spi_config_s {
	int fd;
	char bits_per_word;
	int lsb;
	unsigned int chip_select;
	unsigned int frequency;
	peripheral_spi_mode_e mode;
};

typedef struct peripheral_spi_config_s * peripheral_spi_context_h;

peripheral_spi_context_h peripheral_spi_open(unsigned int bus, peripheral_spi_context_h config);

int	peripheral_spi_write(peripheral_spi_context_h hnd, char *txbuf, int length);

int	peripheral_spi_recv(peripheral_spi_context_h hnd, char *rxbuf, int length);

int peripheral_spi_transfer_buf(peripheral_spi_context_h hnd, char *txbuf, char *rxbuf, int length);

int	peripheral_spi_close(peripheral_spi_context_h hnd);

/**
* @}
*/

#ifdef __cplusplus
}
#endif

#endif /* __PERIPHERAL_IO_H__ */
