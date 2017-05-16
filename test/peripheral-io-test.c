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

#include "peripheral_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gio/gio.h>

extern int gpio_test();
extern int i2c_test();
extern int adc_test();

GMainLoop *loop;

int gpio_test(void)
{
	int num;
	int cnt = 0;
	peripheral_gpio_h handle = NULL;

	printf("artik5 : 135 \n");
	printf("artik10 : 22 \n");
	printf(">> PIN NUMBER : ");

	if (scanf("%d", &num) < 0)
		return 0;
	printf("num %d\n", num);

	if (peripheral_gpio_open(num, &handle) != PERIPHERAL_ERROR_NONE) {
		printf("handle is null\n");
		return 0;
	}

	if (peripheral_gpio_set_direction(handle, PERIPHERAL_GPIO_DIRECTION_OUT) != PERIPHERAL_ERROR_NONE) {
		printf("set direction error!!!");
		goto error;
	}

	while (cnt++ < 5) {
		printf("write~\n");
		peripheral_gpio_write(handle, 1);
		sleep(1);
		peripheral_gpio_write(handle, 0);
		sleep(1);
	}
	printf("write finish\n");
	peripheral_gpio_close(handle);
	return 1;

error:
	peripheral_gpio_close(handle);
	return 0;
}

void gpio_irq_test_isr(void *user_data)
{
	int pin;
	peripheral_gpio_h gpio = user_data;

	peripheral_gpio_get_pin(gpio, &pin);

	printf("gpio_irq_test_isr: GPIO %d interrupt occurs.\n", pin);
}

void *gpio_irq_test_thread(void *data)
{
	peripheral_gpio_h gpio = data;
	int num;

	printf(">> Press any key to exit GPIO IRQ Test : \n");
	if (scanf("%d", &num) < 0)
		return 0;

	peripheral_gpio_unregister_cb(gpio);
	peripheral_gpio_close(gpio);

	g_main_loop_quit(loop);
	return 0;
}

int gpio_irq_test(void)
{
	GThread *test_thread;
	int num;
	peripheral_gpio_h gpio = NULL;
	peripheral_gpio_edge_e edge = PERIPHERAL_GPIO_EDGE_NONE;

	printf("artik710 : 27 \n");
	printf(">> PIN NUMBER : ");

	if (scanf("%d", &num) < 0)
		return 0;

	if (peripheral_gpio_open(num, &gpio) != PERIPHERAL_ERROR_NONE) {
		printf("test dev is null\n");
		return 0;
	}

	if (peripheral_gpio_set_direction(gpio, PERIPHERAL_GPIO_DIRECTION_IN) != 0) {
		printf("test set direction error!!!");
		goto error;
	}

	printf(">> Select Edge Mode (0 = None, 1 = Falling, 2 = Rising, 3 = Both) : ");
	if (scanf("%d", &num) < 0)
		return 0;

	if (num >= 0 && num <= 3)
		edge = num;

	peripheral_gpio_set_edge_mode( gpio, edge);
	peripheral_gpio_register_cb(gpio, gpio_irq_test_isr, gpio);

	test_thread = g_thread_new("key input thread", &gpio_irq_test_thread, gpio);
	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);

	g_thread_join(test_thread);
	if (loop != NULL)
		g_main_loop_unref(loop);

	return 0;

error:
	peripheral_gpio_close(gpio);
	return 0;
}

/* Address of GY30 light sensor */
#define GY30_ADDR 0x23

/* Start measurement at 11x resolution. Measurement time is approx 120ms. */
#define GY30_CONT_HIGH_RES_MODE 0x10

#define GY30_READ_INTENSITY(buf) ((buf[0] << 8 | buf[1]) / 1.2)

int i2c_test(void)
{
	int cnt = 0;
	int bus_num;
	unsigned char buf[10];
	peripheral_i2c_h i2c;

	printf(">> I2C bus number : ");
	if (scanf("%d", &bus_num) < 0)
		return 0;

	if ((peripheral_i2c_open(bus_num, GY30_ADDR, &i2c)) != 0) {
		printf("Failed to open I2C communication\n");
		return 0;
	}

	buf[0] = GY30_CONT_HIGH_RES_MODE;
	if (peripheral_i2c_write(i2c, buf, 1) != 0) {
		printf("Failed to write\n");
		goto error;
	}

	while (cnt++ < 15) {
		int result;
		sleep(1);
		peripheral_i2c_read(i2c, buf, 2);
		result = GY30_READ_INTENSITY(buf);
		printf("Result [%d]\n", result);
	}

	peripheral_i2c_close(i2c);
	return 1;

error:
	peripheral_i2c_close(i2c);
	return 0;
}

int adc_test(void)
{
#if 0
	int channel = 0;
	int data = 0;
	adc_context_h dev = NULL;

	printf(">>channel :");
	scanf("%d", &channel);

	dev = peripheral_adc_open(channel);

	if (!dev) {
		printf("open error!\n");
		return 1;
	}

	peripheral_adc_read(dev, &data);

	peripheral_adc_close(dev);
#endif
	return 1;
}

int pwm_test_led(void)
{
	int device = 0, channel = 0;
	int period = 1 * 1000;
	int duty_cycle = 1 * 1000 / 100;
	int cnt = 0;

	int set_duty_cycle;
	int get_period, get_duty_cycle;
	peripheral_pwm_h dev;

	printf("<<< pwm_test >>>\n");

	peripheral_pwm_open(device, channel, &dev);
	peripheral_pwm_set_period(dev, period);	/* period: nanosecond */
	peripheral_pwm_set_duty_cycle(dev, duty_cycle);	/* duty_cycle: nanosecond */
	peripheral_pwm_set_enable(dev, 1);	/* 0: disable, 1: enable */

	while (cnt < 5) {
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
	int device = 0, channel = 0;
	int period = 20000000;
	int duty_cycle = 1500000;
	int cnt = 0, idx = 0;
	int degree[3] = {0, 45, 90};
	peripheral_pwm_h dev;

	printf("<<< pwm_test_motor >>>\n");

	peripheral_pwm_open(device, channel, &dev);
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

int main(int argc, char **argv)
{
	int num = 1;
	int ret;

	printf("===================\n");
	printf("  test Menu\n");
	printf("===================\n");
	printf(" 1. GPIO Test\n");
	printf(" 2. I2C Test\n");
	printf(" 3. pwm led test\n");
	printf(" 4. pwm motor test\n");

	printf(" 11. GPIO Interrupt Test\n");
	printf(" 12. H/W IF I2C Test\n");
	printf(" 13. H/W IF PWM Test\n");
	printf(" 14. H/W IF SPI Test\n");

	if (scanf("%d", &num) < 0)
		return 0;

	switch (num) {
	case 1:
		ret = gpio_test();
		break;
	case 2:
		ret = i2c_test();
		break;
	case 3:
		ret = pwm_test_led();
		break;
	case 4:
		ret = pwm_test_motor();
		break;
	case 11:
		ret = gpio_irq_test();
		break;
	case 12:
		ret = i2c_test();
		break;
	case 14:
		ret = adc_test();
		break;
	default:
		printf("Not support \n");
	}
	printf(" return : %d\n", ret);

	return 1;
}
