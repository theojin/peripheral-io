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

/**
 * @ingroup   CAPI_SYSTEM_FRAMEWORK
 * @defgroup  CAPI_SYSTEM_PERIPHERAL_IO_MODULE Peripheral IO
 * @brief     The @ref CAPI_SYSTEM_PERIPHERAL_IO_MODULE API provides functions to make use of peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_MODULE_HEADER Required Header
 *            \#include <peripheral_io.h>
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_MODULE_OVERVIEW Overview
 * This @ref CAPI_SYSTEM_PERIPHERAL_IO_MODULE API provides access to the low level device providers,
 * including GPIO, I2C, PWM, ADC, UART and SPI.
 */


/**
 * @ingroup   CAPI_SYSTEM_PERIPHERAL_IO_MODULE
 * @defgroup  CAPI_SYSTEM_PERIPHERAL_IO_GPIO_MODULE GPIO
 * @brief     The @ref CAPI_SYSTEM_PERIPHERAL_IO_GPIO_MODULE API provides functions to control GPIO peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_GPIO_MODULE_HEADER Required Header
 *            \#include <peripheral_io.h>
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_GPIO_MODULE_OVERVIEW Overview
 *
 * This @ref CAPI_SYSTEM_PERIPHERAL_IO_GPIO_MODULE API provides functions to control GPIO peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_GPIO_MODULE_FEATURE Realted Features
 *
 * This API is related with the following feature:\n
 * - http://tizen.org/feature/peripheral_io.gpio\n
 *
 * It is recommended to use features in your application for reliability.\n
 *
 * You can check if a IoT device supports the related features for this API \n
 * by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, and control your application's actions accordingly.\n
 *
 * To ensure your application is only running on the IoT device with specific features, \n
 * please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="https://developer.tizen.org/development/tizen-studio/native-tools/configuring-your-app/manifest-text-editor#feature"><b>Feature Element</b>.</a>
 */


/**
 * @ingroup   CAPI_SYSTEM_PERIPHERAL_IO_MODULE
 * @defgroup  CAPI_SYSTEM_PERIPHERAL_IO_I2C_MODULE I2C
 * @brief     The @ref CAPI_SYSTEM_PERIPHERAL_IO_I2C_MODULE API provides functions to control I2C peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_I2C_MODULE_HEADER Required Header
 *            \#include <peripheral_io.h>
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_I2C_MODULE_OVERVIEW Overview
 *
 * This @ref CAPI_SYSTEM_PERIPHERAL_IO_I2C_MODULE API provides functions to control I2C peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_I2C_MODULE_FEATURE Realted Features
 *
 * This API is related with the following feature:\n
 * - http://tizen.org/feature/peripheral_io.i2c\n
 *
 * It is recommended to use features in your application for reliability.\n
 *
 * You can check if a IoT device supports the related features for this API \n
 * by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, and control your application's actions accordingly.\n
 *
 * To ensure your application is only running on the IoT device with specific features, \n
 * please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="https://developer.tizen.org/development/tizen-studio/native-tools/configuring-your-app/manifest-text-editor#feature"><b>Feature Element</b>.</a>
 */


/**
 * @ingroup   CAPI_SYSTEM_PERIPHERAL_IO_MODULE
 * @defgroup  CAPI_SYSTEM_PERIPHERAL_IO_SPI_MODULE SPI
 * @brief     The @ref CAPI_SYSTEM_PERIPHERAL_IO_SPI_MODULE API provides functions to control SPI peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_SPI_MODULE_HEADER Required Header
 *            \#include <peripheral_io.h>
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_SPI_MODULE_OVERVIEW Overview
 *
 * This @ref CAPI_SYSTEM_PERIPHERAL_IO_SPI_MODULE API provides functions to control SPI peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_SPI_MODULE_FEATURE Realted Features
 *
 * This API is related with the following feature:\n
 * - http://tizen.org/feature/peripheral_io.spi\n
 *
 * It is recommended to use features in your application for reliability.\n
 *
 * You can check if a IoT device supports the related features for this API \n
 * by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, and control your application's actions accordingly.\n
 *
 * To ensure your application is only running on the IoT device with specific features, \n
 * please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="https://developer.tizen.org/development/tizen-studio/native-tools/configuring-your-app/manifest-text-editor#feature"><b>Feature Element</b>.</a>
 */


/**
 * @ingroup   CAPI_SYSTEM_PERIPHERAL_IO_MODULE
 * @defgroup  CAPI_SYSTEM_PERIPHERAL_IO_UART_MODULE UART
 * @brief     The @ref CAPI_SYSTEM_PERIPHERAL_IO_UART_MODULE API provides functions to control UART peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_UART_MODULE_HEADER Required Header
 *            \#include <peripheral_io.h>
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_UART_MODULE_OVERVIEW Overview
 *
 * This @ref CAPI_SYSTEM_PERIPHERAL_IO_UART_MODULE API provides functions to control UART peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_UART_MODULE_FEATURE Realted Features
 *
 * This API is related with the following feature:\n
 * - http://tizen.org/feature/peripheral_io.uart\n
 *
 * It is recommended to use features in your application for reliability.\n
 *
 * You can check if a IoT device supports the related features for this API \n
 * by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, and control your application's actions accordingly.\n
 *
 * To ensure your application is only running on the IoT device with specific features, \n
 * please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="https://developer.tizen.org/development/tizen-studio/native-tools/configuring-your-app/manifest-text-editor#feature"><b>Feature Element</b>.</a>
 */


/**
 * @ingroup   CAPI_SYSTEM_PERIPHERAL_IO_MODULE
 * @defgroup  CAPI_SYSTEM_PERIPHERAL_IO_PWM_MODULE PWM
 * @brief     The @ref CAPI_SYSTEM_PERIPHERAL_IO_PWM_MODULE API provides functions to control PWM peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_PWM_MODULE_HEADER Required Header
 *            \#include <peripheral_io.h>
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_PWM_MODULE_OVERVIEW Overview
 *
 * This @ref CAPI_SYSTEM_PERIPHERAL_IO_PWM_MODULE API provides functions to control PWM peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_PWM_MODULE_FEATURE Realted Features
 *
 * This API is related with the following feature:\n
 * - http://tizen.org/feature/peripheral_io.pwm\n
 *
 * It is recommended to use features in your application for reliability.\n
 *
 * You can check if a IoT device supports the related features for this API \n
 * by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, and control your application's actions accordingly.\n
 *
 * To ensure your application is only running on the IoT device with specific features, \n
 * please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="https://developer.tizen.org/development/tizen-studio/native-tools/configuring-your-app/manifest-text-editor#feature"><b>Feature Element</b>.</a>
 */


/**
 * @ingroup   CAPI_SYSTEM_PERIPHERAL_IO_MODULE
 * @defgroup  CAPI_SYSTEM_PERIPHERAL_IO_ADC_MODULE ADC
 * @brief     The @ref CAPI_SYSTEM_PERIPHERAL_IO_ADC_MODULE API provides functions to control ADC peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_ADC_MODULE_HEADER Required Header
 *            \#include <peripheral_io.h>
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_ADC_MODULE_OVERVIEW Overview
 *
 * This @ref CAPI_SYSTEM_PERIPHERAL_IO_ADC_MODULE API provides functions to control ADC peripherals connected to the IoT device.
 *
 * @section   CAPI_SYSTEM_PERIPHERAL_IO_ADC_MODULE_FEATURE Realted Features
 *
 * This API is related with the following feature:\n
 * - http://tizen.org/feature/peripheral_io.adc\n
 *
 * It is recommended to use features in your application for reliability.\n
 *
 * You can check if a IoT device supports the related features for this API \n
 * by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, and control your application's actions accordingly.\n
 *
 * To ensure your application is only running on the IoT device with specific features, \n
 * please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="https://developer.tizen.org/development/tizen-studio/native-tools/configuring-your-app/manifest-text-editor#feature"><b>Feature Element</b>.</a>
 */
