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

/* Userspace driver for MMA7455 Accelerometer */

#include <stdio.h>

#include "peripheral_io.h"
#include "mma7455.h"

static peripheral_i2c_h mma7455_i2c;
static peripheral_gpio_h isr_gpio;
static peripheral_spi_h mma7455_spi;

#define LOG(...) printf(__VA_ARGS__)

int mma7455_i2c_init(int bus_num)
{
	int ret;

	/* Return if it's already initialized */
	if (mma7455_i2c) {
		LOG("Device was already initialized\n");
		return -1;
	}

	/* Open I2c communication */
	ret = peripheral_i2c_open(bus_num, MMA7455_ADDRESS, &mma7455_i2c);
	if (ret < PERIPHERAL_ERROR_NONE) {
		LOG(">>>>> Failed to open I2C communication, ret : %d \n", ret);
		return -1;
	}

	/* Set mode control register */
	ret = peripheral_i2c_write_register_byte(mma7455_i2c, MMA7455_MCTL,
				MMA7455_MCTL_2G | MMA7455_MCTL_PULSE_DETECTION_MODE);
	if (ret < PERIPHERAL_ERROR_NONE) {
		LOG(">>>>> Failed to write, ret : %d\n", ret);
		peripheral_i2c_close(mma7455_i2c);
		mma7455_i2c = NULL;

		return -1;
	}

	return 0;
}

int mma7455_i2c_close()
{
	int ret;

	if (!mma7455_i2c) {
		LOG("Device is not initialized\n");
		return -1;
	}

	/* Set the device to standby mode */
	peripheral_i2c_write_register_byte(mma7455_i2c, MMA7455_MCTL, MMA7455_MCTL_STANDBY_MODE);

	/* Close I2C communication */
	ret = peripheral_i2c_close(mma7455_i2c);
	if (ret < PERIPHERAL_ERROR_NONE)
		LOG("Failed to close i2c communication, continue anyway\n");

	mma7455_i2c = NULL;

	/* If gpio for interrupt was registered, unregister it */
	if (isr_gpio) {
		peripheral_gpio_unregister_cb(isr_gpio);
		peripheral_gpio_close(isr_gpio);

		isr_gpio = NULL;
	}

	return ret;
}

int mma7455_i2c_reset_isr()
{
	int ret;

	if (!mma7455_i2c) {
		LOG("Device is not initialized\n");
		return -1;
	}

	/* Reset interrupt flags */
	ret = peripheral_i2c_write_register_byte(mma7455_i2c, MMA7455_INTRST, MMA7455_INTRST_CLRINT);
	if (ret < PERIPHERAL_ERROR_NONE)
		goto error;

	ret = peripheral_i2c_write_register_byte(mma7455_i2c, MMA7455_INTRST, MMA7445_INTRST_DONOTCLR);
	if (ret < PERIPHERAL_ERROR_NONE)
		goto error;

	return 0;

error:
	LOG(">>>>> Failed to reset interrupt flags\n");
	return ret;
}

int mma7455_i2c_get_measurement_1(mma7455_axes *result)
{
	unsigned char buf[4];

	if (!mma7455_i2c) {
		LOG("Device is not initialized\n");
		return -1;
	}

	/* Read measurement data from register respectively */
	buf[0] = MMA7455_XOUT8;
	peripheral_i2c_write(mma7455_i2c, buf, 0x1);
	peripheral_i2c_read(mma7455_i2c, &result->x_pos, 0x1);

	buf[0] = MMA7455_YOUT8;
	peripheral_i2c_write(mma7455_i2c, buf, 0x1);
	peripheral_i2c_read(mma7455_i2c, &result->y_pos, 0x1);

	buf[0] = MMA7455_ZOUT8;
	peripheral_i2c_write(mma7455_i2c, buf, 0x1);
	peripheral_i2c_read(mma7455_i2c, &result->z_pos, 0x1);

	return 0;
}

int mma7455_i2c_get_measurement_2(mma7455_axes *result)
{
	if (!mma7455_i2c) {
		LOG("Device is not initialized\n");
		return -1;
	}

	/* Read measurement data by using i2c_write_byte and i2c_read_byte (SMBUS ioctl) */
	peripheral_i2c_write_byte(mma7455_i2c, MMA7455_XOUT8);
	peripheral_i2c_read_byte(mma7455_i2c, &result->x_pos);

	peripheral_i2c_write_byte(mma7455_i2c, MMA7455_YOUT8);
	peripheral_i2c_read_byte(mma7455_i2c, &result->y_pos);

	peripheral_i2c_write_byte(mma7455_i2c, MMA7455_ZOUT8);
	peripheral_i2c_read_byte(mma7455_i2c, &result->z_pos);

	return 0;
}

int mma7455_i2c_get_measurement_3(mma7455_axes *result)
{
	if (!mma7455_i2c) {
		LOG("Device is not initialized\n");
		return -1;
	}

	/* Read measurement data by using i2c_read_register_byte (SMBUS ioctl) */
	peripheral_i2c_read_register_byte(mma7455_i2c, MMA7455_XOUT8, &result->x_pos);
	peripheral_i2c_read_register_byte(mma7455_i2c, MMA7455_YOUT8, &result->y_pos);
	peripheral_i2c_read_register_byte(mma7455_i2c, MMA7455_ZOUT8, &result->z_pos);

	return 0;
}

int mma7455_i2c_register_isr(const int gpio_num, gpio_isr_cb cb_func)
{
	int ret;

	if (!mma7455_i2c) {
		LOG("Device is not initialized\n");
		return -1;
	}

	LOG("mma7455_i2c_register_isr\n");

	if (gpio_num < 0) {
		LOG(">>>>> Wrong gpio number\n");
		return -EINVAL;
	}

	if (isr_gpio != NULL) {
		LOG(">>>>> GPIO ISR is already registered\n");
		return -EBUSY;
	}

	ret = peripheral_gpio_open(gpio_num, &isr_gpio);
	if (ret < PERIPHERAL_ERROR_NONE) {
		LOG(">>>> Failed to open the GPIO pin\n");
		return ret;
	}

	peripheral_gpio_set_direction(isr_gpio, PERIPHERAL_GPIO_DIRECTION_IN);
	peripheral_gpio_set_edge_mode(isr_gpio, PERIPHERAL_GPIO_EDGE_RISING);

	ret = peripheral_gpio_register_cb(isr_gpio, cb_func, NULL);
	if (ret < PERIPHERAL_ERROR_NONE) {
		LOG(">>>> Failed to register gpio callback\n");
		goto error;
	}

	return 0;

error:
	peripheral_gpio_close(isr_gpio);
	isr_gpio = NULL;

	return ret;
}

int mma7455_i2c_unregister_isr()
{
	if (!mma7455_i2c) {
		LOG("Device is not initialized\n");
		return -1;
	}

	/* Check whether GPIO ISR is registered */
	if (isr_gpio == NULL) {
		LOG("GPIO ISR is not registered\n");
		return -1;
	}

	/* Unregister callback and close the pin */
	peripheral_gpio_unregister_cb(isr_gpio);
	peripheral_gpio_close(isr_gpio);

	isr_gpio = NULL;

	return 0;
}

static int mma7455_spi_mctl_write_byte(unsigned char value)
{
	unsigned char tx_buf[2];
	int ret;

	if (!mma7455_spi) {
		LOG("Device is not initialized\n");
		return PERIPHERAL_ERROR_INVALID_OPERATION;
	}

	tx_buf[0] = MMA7455_SPI_REGISTER_WRITE | (MMA7455_MCTL << 1);
	tx_buf[1] = value;

	if ((ret = peripheral_spi_write(mma7455_spi, tx_buf, 2)) < 0)
		return ret;

	return PERIPHERAL_ERROR_NONE;
}

int mma7455_spi_init(int bus_num, int cs_num)
{
	unsigned int num;
	int ret;

	/* Return if it's already initialized */
	if (mma7455_spi) {
		LOG("Device was already initialized\n");
		return -1;
	}

	/* Open SPI communication */
	ret = peripheral_spi_open(bus_num, cs_num, &mma7455_spi);
	if (ret < PERIPHERAL_ERROR_NONE) {
		LOG("Failed to open SPI communication, ret : %d\n", ret);
		return -1;
	}

	peripheral_spi_set_mode(mma7455_spi, PERIPHERAL_SPI_MODE_0);
	peripheral_spi_set_lsb_first(mma7455_spi, false);
	peripheral_spi_set_bits_per_word(mma7455_spi, 8);
	peripheral_spi_set_frequency(mma7455_spi, 8*1024*1024);

	LOG("bus : %d, cs : %d, ", bus_num, cs_num);
	peripheral_spi_get_mode(mma7455_spi, (peripheral_spi_mode_e*)&num);
	LOG("mode : %d, ", num);
	peripheral_spi_get_lsb_first(mma7455_spi, (bool*)&num);
	LOG("lsb first : %d, ", (bool)num);
	peripheral_spi_get_bits_per_word(mma7455_spi, (unsigned char*)&num);
	LOG("bits : %d, ", (unsigned char)num);
	peripheral_spi_get_frequency(mma7455_spi, &num);
	LOG("max frequency : %d\n", num);

	/* Set mode control register */
	ret = mma7455_spi_mctl_write_byte(MMA7455_MCTL_SPI3W
				| MMA7455_MCTL_2G
				| MMA7455_MCTL_MEASUREMENT_MODE);
	if (ret < PERIPHERAL_ERROR_NONE) {
		LOG("Failed to write, ret : %d\n", ret);
		peripheral_spi_close(mma7455_spi);
		mma7455_spi = NULL;

		return -1;
	}

	return 0;
}

int mma7455_spi_close()
{
	int ret;

	if (!mma7455_spi) {
		LOG("Device is not initialized\n");
		return -1;
	}

	/* Set the device to standby mode */
	ret = mma7455_spi_mctl_write_byte(MMA7455_MCTL_STANDBY_MODE);
	if (ret < PERIPHERAL_ERROR_NONE)
		LOG("Failed to set the device to standby mode\n");

	ret = peripheral_spi_close(mma7455_spi);
	if (ret < PERIPHERAL_ERROR_NONE)
		LOG("Failed to close i2c communication, continue anyway\n");

	mma7455_spi = NULL;

	return 0;
}

int mma7455_spi_get_measurement(mma7455_axes *result)
{
	unsigned char tx_data;

	if (!mma7455_spi) {
		LOG("Device is not initialized\n");
		return -1;
	}

	/* Read measurement value */
	tx_data = MMA7455_XOUT8 << 1;
	peripheral_spi_read_write(mma7455_spi, &tx_data, &(result->x_pos), 1);
	tx_data = MMA7455_YOUT8 << 1;
	peripheral_spi_read_write(mma7455_spi, &tx_data, &(result->y_pos), 1);
	tx_data = MMA7455_ZOUT8 << 1;
	peripheral_spi_read_write(mma7455_spi, &tx_data, &(result->z_pos), 1);

	return 0;
}
