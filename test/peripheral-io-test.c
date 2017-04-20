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

extern int gpio_test();
extern int i2c_test();
extern int adc_test();

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
	peripheral_i2c_h dev;

	printf(">> I2C bus number : ");
	if (scanf("%d", &bus_num) < 0)
		return 0;

	if ((dev = peripheral_i2c_init(bus_num)) == NULL) {
		printf("Failed to initialize I2C device\n");
		return 0;
	}

	if (peripheral_i2c_set_address(dev, GY30_ADDR) != 0) {
		printf("Failed to set address\n");
		goto error;
	}

	buf[0] = GY30_CONT_HIGH_RES_MODE;
	if (peripheral_i2c_write(dev, buf, 1) != 0) {
		printf("Failed to write\n");
		goto error;
	}

	while (cnt++ < 15) {
		int result;
		sleep(1);
		peripheral_i2c_read(dev, buf, 2);
		result = GY30_READ_INTENSITY(buf);
		printf("Result [%d]\n", result);
	}

	peripheral_i2c_stop(dev);
	return 1;

error:
	peripheral_i2c_stop(dev);
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
	peripheral_pwm_context_h dev;

	printf("<<< pwm_test >>>\n");

	dev = peripheral_pwm_open(device, channel);
	peripheral_pwm_set_period(dev, period);	/* period: nanosecond */
	peripheral_pwm_set_duty_cycle(dev, duty_cycle);	/* duty_cycle: nanosecond */
	peripheral_pwm_set_enabled(dev, 1);	/* 0: disable, 1: enable */

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
	peripheral_pwm_set_enabled(dev, 0);	/* 0: disable, 1: enable */
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
	peripheral_pwm_context_h dev;

	printf("<<< pwm_test_motor >>>\n");

	dev = peripheral_pwm_open(device, channel);
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
			peripheral_pwm_set_enabled(dev, 1);		/* 0: disable, 1: enable */
			usleep(500000);
		}
	}

	peripheral_pwm_set_enabled(dev, 0);	/* 0: disable, 1: enable */
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

	printf(" 11. H/W IF GPIO Test\n");
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
		ret = gpio_test();
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