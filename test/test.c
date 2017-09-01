#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <peripheral_io.h>
#include <glib.h>

#define RETURN_IF_ERROR(err) \
if (err < 0) { \
	printf("[%d] Error : %d", __LINE__, err); \
	return 0; \
}

#define INT_PIN 19

GMainLoop *main_loop;

static void gpio_test(gpio_isr_cb_s *data, void *user_data)
{
	int value;
	peripheral_gpio_h gpio = user_data;

	peripheral_gpio_read(gpio, &value);

	printf("Interrupted : %d, %d\n", value, data->value);
}

int main(int argc, char *argv[])
{
	peripheral_gpio_h gpio = NULL;
	int err;

	err = peripheral_gpio_open(INT_PIN, &gpio);
	RETURN_IF_ERROR(err);

	err = peripheral_gpio_set_direction(gpio, PERIPHERAL_GPIO_DIRECTION_IN);
	RETURN_IF_ERROR(err);

	err = peripheral_gpio_set_edge_mode(gpio, PERIPHERAL_GPIO_EDGE_RISING);
	RETURN_IF_ERROR(err);

	err = peripheral_gpio_register_cb(gpio, gpio_test, gpio);
	RETURN_IF_ERROR(err);

	printf("Success!!!!\n");

	main_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(main_loop);
	g_main_loop_unref(main_loop);

	err = peripheral_gpio_close(gpio);
	RETURN_IF_ERROR(err);

	return 0;
}
