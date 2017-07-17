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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <gio/gio.h>

#include "peripheral_io.h"

#include "mma7455.h"

#define BUFFER_LEN 32

typedef struct {
	int cnt;
	peripheral_gpio_h gpio_trig;
	peripheral_gpio_h gpio_echo;
} gpio_hcsr04_module_s;

typedef struct {
	const char *tc_name;
	int tc_code;
	int (*tc_func)(void);
} tc_table_t;

tc_table_t *tc_table;

GMainLoop *main_loop;
GList *gpio_list;
GList *i2c_list;
GList *pwm_list;
GList *adc_list;
GList *uart_list;
GList *spi_list;

int read_int_input(int *input)
{
	char buf[BUFFER_LEN];
	int rv;

	rv = read(0, buf, BUFFER_LEN);

	/* Ignore Enter without value */
	if (*buf == '\n' || *buf == '\r') {
		printf("No input value\n");
		return -1;
	}

	if (rv < 0) return -1;
	*input = atoi(buf);

	return 0;
}

int gpio_led_test(void)
{
	int num, ret;
	int cnt = 0;
	peripheral_gpio_h handle = NULL;

	printf("    %s()\n", __func__);
	printf("Enter GPIO pin number ");

	if (scanf("%d", &num) < 0)
		return -1;
	printf("num %d\n", num);

	if ((ret = peripheral_gpio_open(num, &handle)) < PERIPHERAL_ERROR_NONE) {
		printf("Failed to open\n");
		return ret;
	}

	if ((ret = peripheral_gpio_set_direction(handle, PERIPHERAL_GPIO_DIRECTION_OUT)) < PERIPHERAL_ERROR_NONE) {
		printf("Failed to set direction!!\n");
		goto error;
	}

	while (cnt++ < 5) {
		printf("Writing..\n");
		peripheral_gpio_write(handle, 1);
		sleep(1);
		peripheral_gpio_write(handle, 0);
		sleep(1);
	}
	printf("Write finish\n");
	if ((ret = peripheral_gpio_close(handle)) < PERIPHERAL_ERROR_NONE) {
		printf("Failed to close the pin\n");
		return ret;
	}

	return 0;

error:
	peripheral_gpio_close(handle);
	return ret;
}

void gpio_irq_test_isr(gpio_isr_cb_s *data, void *user_data)
{
	int pin;
	peripheral_gpio_h gpio = user_data;

	peripheral_gpio_get_pin(gpio, &pin);

	printf("%s: GPIO %d interrupt occurs.\n", __func__, pin);
}

int gpio_irq_register(void)
{
	peripheral_gpio_h gpio = NULL;
	int pin, ret;

	printf("    %s()\n", __func__);
	printf("Enter gpio pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if ((ret = peripheral_gpio_open(pin, &gpio)) < 0) {
		printf(">>>>> Failed to open GPIO pin, ret : %d\n", ret);
		return -1;
	}
	gpio_list = g_list_append(gpio_list, gpio);

	if ((ret = peripheral_gpio_set_direction(gpio, PERIPHERAL_GPIO_DIRECTION_IN)) < 0) {
		printf(">>>>> Failed to set direction, ret : %d\n", ret);
		goto error;
	}
	peripheral_gpio_set_edge_mode(gpio, PERIPHERAL_GPIO_EDGE_BOTH);
	peripheral_gpio_register_cb(gpio, gpio_irq_test_isr, gpio);

	return 0;

error:
	gpio_list = g_list_remove(gpio_list, gpio);
	peripheral_gpio_close(gpio);
	return -1;
}

int gpio_irq_unregister(void)
{
	peripheral_gpio_h gpio;
	int pin, ret;
	int gpio_test_get_handle_by_pin(int pin, peripheral_gpio_h *gpio);

	printf("    %s()\n", __func__);
	printf("Enter gpio pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if (gpio_test_get_handle_by_pin(pin, &gpio) < 0) {
		printf(">>>>> cannot find handle. please open the gpio pin.\n");
		return -1;
	}

	if ((ret = peripheral_gpio_unregister_cb(gpio)) < 0) {
		printf(">>>>> failed to unregister callback function, ret : %d\n", ret);
		return -1;
	}

	gpio_list = g_list_remove(gpio_list, gpio);
	peripheral_gpio_close(gpio);

	return 0;
}

/* Address of GY30 light sensor */
#define GY30_ADDR 0x23

/* Start measurement at 11x resolution. Measurement time is approx 120ms. */
#define GY30_CONT_HIGH_RES_MODE 0x10

#define GY30_READ_INTENSITY(buf) ((buf[0] << 8 | buf[1]) / 1.2)

int i2c_gy30_test(void)
{
	int cnt = 0;
	unsigned char buf[10];
	peripheral_i2c_h i2c;
	struct timeval tv_1, tv_2;
	int bus_num, ret, result, interval;

	printf("    %s()\n", __func__);
	printf("Enter I2C bus number\n");

	if (read_int_input(&bus_num) < 0)
		return -1;

	if ((ret = peripheral_i2c_open(bus_num, GY30_ADDR, &i2c)) < 0) {
		printf("Failed to open I2C communication, ret : %d\n", ret);
		return -1;
	}

	if ((ret = peripheral_i2c_write_byte(i2c, GY30_CONT_HIGH_RES_MODE)) < 0) {
		printf("Failed to write, ret : %d\n", ret);
		goto error;
	}

	gettimeofday(&tv_1, NULL);
	while (cnt++ < 1000) {
		ret = peripheral_i2c_read(i2c, buf, 2);
		if (ret < 0)
			printf("Failed to read, ret : %d\n", ret);
		result = GY30_READ_INTENSITY(buf);
		printf("Light intensity : %d\n", result);
	}
	gettimeofday(&tv_2, NULL);
	interval = (tv_2.tv_sec - tv_1.tv_sec) * 1000 + (int)(tv_2.tv_usec - tv_1.tv_usec)/1000;
	printf("1000 i2c read calls took %d ms\n", interval);

	peripheral_i2c_close(i2c);
	return 0;

error:
	peripheral_i2c_close(i2c);
	return -1;
}

static void i2c_mma7455_isr(gpio_isr_cb_s *data, void *user_data)
{
	mma7455_axes result;

	mma7455_i2c_get_measurement_3(&result);
	printf("Result X : %d, Y : %d, Z : %d\n", result.x_pos, result.y_pos, result.z_pos);

	/* Reset interrupt flags */
	mma7455_i2c_reset_isr();

	return;
}

int i2c_mma7455_test(void)
{
	static int gpio_num;
	static bool enable;
	int bus_num;
	int cnt = 0;

	printf("    %s()\n", __func__);
	if (enable) {
		printf("Disabling the test\n");

		mma7455_i2c_unregister_isr();
		mma7455_i2c_close();
		printf("mma7455 is closed\n");

		enable = FALSE;

		return 0;
	}

	printf("Enter I2C bus number\n");

	if (read_int_input(&bus_num) < 0)
		return -1;

	if (mma7455_i2c_init(bus_num) < 0)
		return -1;

	printf("Enter GPIO pin number for Interrupt\n");
	if (read_int_input(&gpio_num) < 0)
		gpio_num = -1;

	if (gpio_num > 0) {
		if (mma7455_i2c_register_isr(gpio_num, i2c_mma7455_isr) != 0)
			return -1;

		/* Reset interrupt flags */
		mma7455_i2c_reset_isr();

		enable = TRUE;

		printf("callback is registered on gpio pin %d\n", gpio_num);
		printf("i2c(bus = %d address = %d) handle is open\n", bus_num, MMA7455_ADDRESS);
	} else {
		while (cnt++ < 10) {
			mma7455_axes result;

			sleep(1);

			/* Get measurement data with different APIs */
			mma7455_i2c_get_measurement_1(&result);
			printf("Result X : %d, Y : %d, Z : %d  (peripheral_i2c_read)\n",
				result.x_pos, result.y_pos, result.z_pos);

			mma7455_i2c_get_measurement_2(&result);
			printf("Result X : %d, Y : %d, Z : %d  (peripheral_i2c_read_byte)\n",
				result.x_pos, result.y_pos, result.z_pos);

			mma7455_i2c_get_measurement_3(&result);
			printf("Result X : %d, Y : %d, Z : %d  (peripheral_i2c_read_register_byte)\n",
				result.x_pos, result.y_pos, result.z_pos);
		}
		mma7455_i2c_close();
		printf("i2c(bus = %d address = %d) handle is closed\n", bus_num, MMA7455_ADDRESS);
	}
	return 0;
}

int pwm_test_led(void)
{
	int device, channel, ret;
	int period = 1 * 1000;
	int duty_cycle = 1 * 1000 / 100;
	int cnt = 0;

	int set_duty_cycle;
	int get_period, get_duty_cycle;
	peripheral_pwm_h dev;

	printf("    %s()\n", __func__);
	printf("Enter PWM device number\n");
	if (read_int_input(&device) < 0)
		return -1;

	printf("Enter PWM channel number\n");
	if (read_int_input(&channel) < 0)
		return -1;

	ret = peripheral_pwm_open(device, channel, &dev);
	if (ret != PERIPHERAL_ERROR_NONE) {
		printf("Failed to open\n");
		return ret;
	}
	peripheral_pwm_set_period(dev, period);	/* period: nanosecond */
	peripheral_pwm_set_duty_cycle(dev, duty_cycle);	/* duty_cycle: nanosecond */
	peripheral_pwm_set_enable(dev, 1);	/* 0: disable, 1: enable */

	while (cnt < 2) {
		for (set_duty_cycle = period; set_duty_cycle > 0; set_duty_cycle -= 50) {
			/* set duty cycle */
			peripheral_pwm_set_duty_cycle(dev, set_duty_cycle);
			peripheral_pwm_get_period(dev, &get_period);
			peripheral_pwm_get_duty_cycle(dev, &get_duty_cycle);
			printf("period(%d), duty_cycle(%d)\n", get_period, get_duty_cycle);
			usleep(500000);
		}
		for (set_duty_cycle = 0; set_duty_cycle < period; set_duty_cycle += 50) {
			/* set duty cycle */
			peripheral_pwm_set_duty_cycle(dev, set_duty_cycle);
			peripheral_pwm_get_period(dev, &get_period);
			peripheral_pwm_get_duty_cycle(dev, &get_duty_cycle);
			printf("period(%d), duty_cycle(%d)\n", get_period, get_duty_cycle);
			usleep(500000);
		}
		cnt++;
	}
	peripheral_pwm_set_enable(dev, 0);	/* 0: disable, 1: enable */
	peripheral_pwm_close(dev);

	return 0;
}

int pwm_test_motor(void)
{
	int device, channel, ret;
	int period = 20000000;
	int duty_cycle = 1500000;
	int cnt = 0, idx = 0;
	int degree[3] = {0, 45, 90};
	peripheral_pwm_h dev;

	printf("    %s()\n", __func__);
	printf("Enter PWM device number\n");
	if (read_int_input(&device) < 0)
		return -1;

	printf("Enter PWM channel number\n");
	if (read_int_input(&channel) < 0)
		return -1;

	ret = peripheral_pwm_open(device, channel, &dev);
	if (ret != PERIPHERAL_ERROR_NONE) {
		printf("Failed to open\n");
		return ret;
	}
	for (cnt = 0; cnt < 5; cnt++) {
		for (idx = 0; idx < 3; idx++) {
			switch (degree[idx]) {
			case 0:
				duty_cycle = 1000000;
				break;
			case 45:
				duty_cycle = 1500000;
				break;
			case 90:
				duty_cycle = 2000000;
				break;
			default:
				duty_cycle = 2000000;
				break;
			}
			printf("set degree: %d\n", degree[idx]);
			peripheral_pwm_set_period(dev, period);
			peripheral_pwm_set_duty_cycle(dev, duty_cycle);
			peripheral_pwm_set_enable(dev, 1);		/* 0: disable, 1: enable */
			usleep(500000);
		}
	}

	peripheral_pwm_set_enable(dev, 0);	/* 0: disable, 1: enable */
	peripheral_pwm_close(dev);

	return 0;
}


int uart_test_accelerometer(void)
{
	peripheral_uart_h uart;
	int ret;
	int port;
	int loop = 100;
	unsigned char buf[1024];

	printf("    %s()\n", __func__);
	printf("Enter port number");

	if (scanf("%d", &port) < 0)
		return -1;

	ret = peripheral_uart_open(port, &uart);
	if (ret < 0)
		goto err_open;

	ret = peripheral_uart_set_baudrate(uart, PERIPHERAL_UART_BAUDRATE_4800);
	if (ret < 0)
		goto out;

	ret = peripheral_uart_set_mode(uart,
			PERIPHERAL_UART_BYTESIZE_8BIT,
			PERIPHERAL_UART_PARITY_NONE,
			PERIPHERAL_UART_STOPBITS_1BIT);
	if (ret < 0)
		goto out;

	ret = peripheral_uart_set_flowcontrol(uart, true, false);
	if (ret < 0)
		goto out;

	sleep(1);
	ret = peripheral_uart_flush(uart);
	if (ret < 0)
		goto out;

	while (loop--) {
		ret = peripheral_uart_read(uart, buf, 13);
		if (ret < 0) {
			if (ret == PERIPHERAL_ERROR_NO_DATA)
				printf("No data to read (%d)\n", ret);
			else
				printf("Failed to read (%d)\n", ret);
			continue;
		}
		buf[ret] = 0;
		printf("%s", buf);
		usleep(100000);
	}

	peripheral_uart_close(uart);
	return 0;

out:
	peripheral_uart_close(uart);

err_open:
	return -1;
}

int spi_mma7455_module_test(void)
{
	int cnt = 0;
	int bus_num, cs_num;
	mma7455_axes result;

	printf("	%s()\n", __func__);
	printf("Enter SPI bus number : ");
	if (scanf("%d", &bus_num) < 0)
		return -1;

	printf("Enter SPI cs number : ");
	if (scanf("%d", &cs_num) < 0)
		return -1;

	if (mma7455_spi_init(bus_num, cs_num) < 0)
		return -1;

	while (cnt++ < 15) {
		sleep(1);
		mma7455_spi_get_measurement(&result);
		printf("Result X : %d, Y : %d, Z : %d\n",
			result.x_pos, result.y_pos, result.z_pos);
	}

	mma7455_spi_close();

	return 0;
}

void gpio_hcsr04_isr(gpio_isr_cb_s *data, void *user_data)
{
	float dist = 0;
	static unsigned long long timestamp = 0;

	if (timestamp > 0 && data->value == 0) {
		dist = data->timestamp - timestamp;
		dist = (dist * 34300) / 2000000;
		printf("%s: Measured Distance : %0.2fcm\n", __func__, dist);
	}

	timestamp = data->timestamp;
}

gboolean gpio_hcsr04_timeout_cb(gpointer data)
{
	gpio_hcsr04_module_s *dev = (gpio_hcsr04_module_s*)data;

	if (dev->cnt--) {
		peripheral_gpio_write(dev->gpio_trig, 1);
		peripheral_gpio_write(dev->gpio_trig, 0);
	} else
		return FALSE;

	return TRUE;
}

void gpio_hcsr04_destroy(gpointer data)
{
	gpio_hcsr04_module_s *dev = (gpio_hcsr04_module_s*)data;

	peripheral_gpio_unregister_cb(dev->gpio_echo);
	peripheral_gpio_close(dev->gpio_echo);
	peripheral_gpio_close(dev->gpio_trig);
	free(dev);
}

int gpio_hcsr04_ultrasonic_ranging_module(void)
{
	gpio_hcsr04_module_s *dev;
	int pin_trig, pin_echo, ret;

	printf("    %s()\n", __func__);
	printf("Enter triger gpio pin number\n");
	if (read_int_input(&pin_trig) < 0)
		return -1;

	printf("Enter echo gpio pin number\n");
	if (read_int_input(&pin_echo) < 0)
		return -1;

	dev = calloc(1, sizeof(gpio_hcsr04_module_s));
	if (dev == NULL) {
		printf("failed to allocate gpio_hcsr04_module_s\n");
		return -1;
	}

	if ((ret = peripheral_gpio_open(pin_trig, &dev->gpio_trig)) < 0) {
		printf(">>>>> Failed to open GPIO pin, ret : %d\n", ret);
		goto err;
	}

	if ((ret = peripheral_gpio_open(pin_echo, &dev->gpio_echo)) < 0) {
		printf(">>>>> Failed to open GPIO pin, ret : %d\n", ret);
		peripheral_gpio_close(dev->gpio_trig);
		goto err;
	}

	peripheral_gpio_set_direction(dev->gpio_echo, PERIPHERAL_GPIO_DIRECTION_IN);
	peripheral_gpio_set_edge_mode(dev->gpio_echo, PERIPHERAL_GPIO_EDGE_BOTH);
	peripheral_gpio_register_cb(dev->gpio_echo, gpio_hcsr04_isr, NULL);
	peripheral_gpio_set_direction(dev->gpio_trig, PERIPHERAL_GPIO_DIRECTION_OUT);

	dev->cnt = 20;

	g_timeout_add_seconds_full(G_PRIORITY_DEFAULT,
					1,
					gpio_hcsr04_timeout_cb,
					dev,
					gpio_hcsr04_destroy);

	return 0;

err:
	free(dev);
	return -1;
}

int gpio_test_get_handle_by_pin(int pin, peripheral_gpio_h *gpio)
{
	peripheral_gpio_h handle;
	GList *cursor;
	int cur_pin;

	cursor = gpio_list;
	while (cursor) {
		handle = (peripheral_gpio_h)cursor->data;
		peripheral_gpio_get_pin(handle, &cur_pin);
		if (pin == cur_pin)
			break;
		cursor = g_list_next(cursor);
	}
	if (!cursor) return -1;

	*gpio = handle;

	return 0;
}

int print_gpio_handle(void)
{
	peripheral_gpio_h gpio;
	GList *cursor;
	peripheral_gpio_direction_e direction;
	peripheral_gpio_edge_e edge;
	int pin, value;
	char *dir_str, *edge_str;

	printf("--- GPIO handle info. -------------------------------------------\n");
	printf("      No     Pin   Direction   Value   Edge mode\n");

	cursor = gpio_list;
	while (cursor) {
		gpio = (peripheral_gpio_h)cursor->data;

		if (peripheral_gpio_get_pin(gpio, &pin) < 0)
			continue;
		if (peripheral_gpio_get_direction(gpio, &direction) < 0)
			continue;
		if (peripheral_gpio_get_edge_mode(gpio, &edge) < 0)
			continue;

		if (direction == PERIPHERAL_GPIO_DIRECTION_IN)
			dir_str = "IN";
		else if (direction == PERIPHERAL_GPIO_DIRECTION_OUT_LOW)
			dir_str = "OUT_LOW";
		else if (direction == PERIPHERAL_GPIO_DIRECTION_OUT_HIGH)
			dir_str = "OUT_HIGH";
		else
			dir_str = "UNKNOWN";

		if (edge == PERIPHERAL_GPIO_EDGE_NONE)
			edge_str = "NONE";
		else if (edge == PERIPHERAL_GPIO_EDGE_RISING)
			edge_str = "RISING";
		else if (edge == PERIPHERAL_GPIO_EDGE_FALLING)
			edge_str = "FALLING";
		else if (edge == PERIPHERAL_GPIO_EDGE_BOTH)
			edge_str = "BOTH";
		else
			edge_str = "UNKNOWN";

		if (direction == PERIPHERAL_GPIO_DIRECTION_IN) {
			if (peripheral_gpio_read(gpio, &value) < 0)
				continue;
			printf("%8d%8d%12s%8d%12s\n", g_list_position(gpio_list, cursor),
					pin, dir_str, value, edge_str);
		} else
			printf("%8d%8d%12s%20s\n", g_list_position(gpio_list, cursor),
					pin, dir_str, edge_str);

		cursor = g_list_next(cursor);
	}
	printf("-----------------------------------------------------------------\n");

	return 0;
}

int gpio_test_open(void)
{
	peripheral_gpio_h gpio;
	int pin, ret;

	printf("%s\n", __func__);
	printf("Enter GPIO pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if ((ret = peripheral_gpio_open(pin, &gpio)) < 0) {
		printf(">>>>> GPIO open failed, ret : %d\n", ret);
		return -1;
	}
	gpio_list = g_list_append(gpio_list, gpio);
	print_gpio_handle();

	return 0;
}

int gpio_test_close(void)
{
	peripheral_gpio_h gpio;
	int pin, ret;

	printf("%s\n", __func__);
	printf("Enter GPIO pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if (gpio_test_get_handle_by_pin(pin, &gpio) < 0) {
		printf(">>>>> Cannot find handle. Please open the GPIO pin\n");
		return -1;
	}
	gpio_list = g_list_remove(gpio_list, gpio);

	if ((ret = peripheral_gpio_close(gpio)) < 0) {
		printf(">>>>> GPIO close failed, ret : %d\n", ret);
		return -1;
	}
	print_gpio_handle();

	return 0;
}

int gpio_test_set_direction(void)
{
	peripheral_gpio_h gpio;
	int pin, ret;
	int direction;

	printf("%s\n", __func__);
	printf("Enter gpio pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if (gpio_test_get_handle_by_pin(pin, &gpio) < 0) {
		printf(">>>>> Cannot find handle. Please open the GPIO pin\n");
		return -1;
	}

	printf("Enter direction (0:IN, 1:OUT_LOW, 2:OUT_HIGH)\n");
	if (read_int_input(&direction) < 0)
		return -1;

	if (direction > PERIPHERAL_GPIO_DIRECTION_OUT_HIGH ||
		direction < PERIPHERAL_GPIO_DIRECTION_IN) {
		printf(">>>>> Wrong input value\n");
		return -1;
	}

	if ((ret = peripheral_gpio_set_direction(gpio, (peripheral_gpio_direction_e)direction)) < 0) {
		printf(">>>>> Failed to set direction, ret : %d\n", ret);
		return -1;
	}

	return 0;
}

int gpio_test_write(void)
{
	peripheral_gpio_h gpio;
	int pin, ret;
	int value;

	printf("%s\n", __func__);
	printf("Enter gpio pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if (gpio_test_get_handle_by_pin(pin, &gpio) < 0) {
		printf(">>>>> Cannot find handle. Please open the GPIO pin\n");
		return -1;
	}

	printf("Enter value (0:LOW, 1:HIGH)\n");
	if (read_int_input(&value) < 0)
		return -1;

	if (value < 0 || value > 1) {
		printf(">>>>> Wrong input value\n");
		return -1;
	}

	if ((ret = peripheral_gpio_write(gpio, value)) < 0) {
		printf(">>>>> Failed to write value, ret : %d\n", ret);
		return -1;
	}

	return 0;
}

int gpio_test_set_edge_mode(void)
{
	peripheral_gpio_h gpio;
	int pin, ret;
	int edge;

	printf("%s\n", __func__);
	printf("Enter gpio pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if (gpio_test_get_handle_by_pin(pin, &gpio) < 0) {
		printf(">>>>> Cannot find handle. Please open the GPIO pin\n");
		return -1;
	}

	printf("Enter edge mode (0:NONE, 1:RISING, 2:FALLING, 3:BOTH)\n");
	if (read_int_input(&edge) < 0)
		return -1;

	if (edge < PERIPHERAL_GPIO_EDGE_NONE || edge > PERIPHERAL_GPIO_EDGE_BOTH) {
		printf(">>>>> Wrong input value\n");
		return -1;
	}

	if ((ret = peripheral_gpio_set_edge_mode(gpio, (peripheral_gpio_edge_e)edge)) < 0) {
		printf(">>>>> Failed to set edge mode, ret : %d\n", ret);
		return -1;
	}

	return 0;
}

int gpio_test_set_register_cb(void)
{
	peripheral_gpio_h gpio;
	int pin, ret;

	printf("%s\n", __func__);
	printf("Enter gpio pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if (gpio_test_get_handle_by_pin(pin, &gpio) < 0) {
		printf(">>>>> Cannot find handle. Please open the GPIO pin\n");
		return -1;
	}

	if ((ret = peripheral_gpio_register_cb(gpio, gpio_irq_test_isr, gpio)) < 0) {
		printf(">>>>> Failed to register callback function, ret : %d\n", ret);
		return -1;
	}
	return 0;
}

int gpio_test_set_unregister_cb(void)
{
	peripheral_gpio_h gpio;
	int pin, ret;

	printf("%s\n", __func__);
	printf("Enter gpio pin number\n");

	if (read_int_input(&pin) < 0)
		return -1;

	if (gpio_test_get_handle_by_pin(pin, &gpio) < 0) {
		printf(">>>>> Cannot find handle. Please open the GPIO pin\n");
		return -1;
	}

	if ((ret = peripheral_gpio_unregister_cb(gpio)) < 0) {
		printf(">>>>> failed to unregister callback function, ret : %d\n", ret);
		return -1;
	}

	return 0;
}

int enter_main(void);

tc_table_t gpio_tc_table[] = {
	{"Open GPIO pin",				1, gpio_test_open},
	{"Close GPIO pin",				2, gpio_test_close},
	{"Set direction GPIO pin",		3, gpio_test_set_direction},
	{"Write value to GPIO pin",		4, gpio_test_write},
	{"Set edge mode",				5, gpio_test_set_edge_mode},
	{"Register callback",			6, gpio_test_set_register_cb},
	{"Unregister callback",			7, gpio_test_set_unregister_cb},
	{"Print GPIO handle",			9, print_gpio_handle},
	{"Go back to main",				0, enter_main},
	{NULL,	0, NULL},
};

int enter_gpio_test(void)
{
	tc_table = gpio_tc_table;
	print_gpio_handle();

	return 0;
}

int enter_i2c_test(void)
{
	return 0;
}

int enter_pwm_test(void)
{
	return 0;
}

int adc_read_channel(void)
{
	int device, channel, ret;
	int value;

	printf("%s\n", __func__);

	printf("Enter adc device number\n");
	if (read_int_input(&device) < 0)
		return -1;

	printf("Enter adc channel number\n");
	if (read_int_input(&channel) < 0)
		return -1;

	if ((ret = peripheral_adc_read(device, channel, &value)) < 0) {
		printf(">>>>> Failed to read adc value, ret : %d\n", ret);
		return -1;
	}
	printf("ADC(%d,%d) Value = %d\n", device, channel, value);

	return 0;
}

tc_table_t adc_tc_table[] = {
	{"Read ADC Channel",			1, adc_read_channel},
	{"Go back to main",				0, enter_main},
	{NULL,	0, NULL},
};

int enter_adc_test(void)
{
	tc_table = adc_tc_table;

	return 0;
}

int enter_uart_test(void)
{
	return 0;
}

int enter_spi_test(void)
{
	return 0;
}

tc_table_t preset_tc_table[] = {
	{"[Preset Test] GPIO LED",					1, gpio_led_test},
	{"[Preset Test] I2C GY30 Light sensor",		2, i2c_gy30_test},
	{"[Preset Test] I2C MMA7455 Accel. sensor",	3, i2c_mma7455_test},
	{"[Preset Test] PWM LED",					4, pwm_test_led},
	{"[Preset Test] PWM Motor",					5, pwm_test_motor},
	{"[Preset Test] Uart Accelerometer",		6, uart_test_accelerometer},
	{"[Preset Test] SPI MMA7455 Accel. sensor",	7, spi_mma7455_module_test},
	{"[Preset Test] GPIO HC-SR04 Range sensor",	8, gpio_hcsr04_ultrasonic_ranging_module},
	{"[Preset Test] GPIO IRQ register",			10, gpio_irq_register},
	{"[Preset Test] GPIO IRQ unregister",		11, gpio_irq_unregister},
	{"Go back to main",							0, enter_main},
	{NULL,	0, NULL},
};

int enter_preset_test(void)
{
	tc_table = preset_tc_table;
	return 0;
}

int terminate_test(void)
{
	int ret = 0;

	printf("Terminate test\n");
	g_main_loop_quit(main_loop);

	exit(1);

	return ret;
}

tc_table_t main_tc_table[] = {
	{"GPIO Test Menu",							1, enter_gpio_test},
	{"I2C Test Menu",							2, enter_i2c_test},
	{"PWM Test Menu",							3, enter_pwm_test},
	{"ADC Test Menu",							4, enter_adc_test},
	{"UART Test Menu",							5, enter_uart_test},
	{"SPI Test Menu",							6, enter_spi_test},
	{"Preset Test",								10, enter_preset_test},
	{"Exit Test",								0, terminate_test},
	{NULL,	0, NULL},
};

int enter_main(void)
{
	tc_table = main_tc_table;

	return 0;
}

static int test_input_callback(void *data)
{
	tc_table_t *tc;
	long test_id = (long)data;
	int ret = PERIPHERAL_ERROR_NONE;
	int i = 0;

	tc = tc_table;

	while (tc[i].tc_name) {
		if (tc[i].tc_code == test_id && tc[i].tc_func) {
			ret = tc[i].tc_func();
			if (ret != PERIPHERAL_ERROR_NONE)
				printf(">>>>> Test Error Returned !!! : %d\n", ret);

			break;
		}
		i++;
	}
	if (!tc[i].tc_name) {
		printf(">>>>> Wrong input value!\n");
		return -1;
	}

	return 0;
}

static void print_tc_usage(void)
{
	int i = 0;

	printf("===========================================\n");
	while (tc_table[i].tc_name) {
		printf("    %2d : %s\n", tc_table[i].tc_code, tc_table[i].tc_name);
		i++;
	}
	printf("===========================================\n");
	printf("Enter TC number\n");
}

static gboolean key_event_cb(GIOChannel *chan, GIOCondition cond, gpointer data)
{
	char buf[BUFFER_LEN] = {0,};
	long test_id;
	int rv = 0;

	memset(buf, 0, sizeof(buf));

	rv = read(0, buf, BUFFER_LEN);

	if (*buf == '\n' || *buf == '\r') {
		print_tc_usage();
		return TRUE;
	}

	if (rv < 0) return FALSE;

	test_id = atoi(buf);

	test_input_callback((void *)test_id);
	print_tc_usage();

	return TRUE;
}

int main(int argc, char **argv)
{
	GIOChannel *key_io;

	main_loop = g_main_loop_new(NULL, FALSE);
	key_io = g_io_channel_unix_new(0);

	tc_table = main_tc_table;

	print_tc_usage();
	g_io_add_watch(key_io, (G_IO_IN | G_IO_HUP | G_IO_ERR | G_IO_NVAL), key_event_cb, NULL);

	g_main_loop_run(main_loop);

	g_io_channel_unref(key_io);
	g_main_loop_unref(main_loop);

	return 0;
}
