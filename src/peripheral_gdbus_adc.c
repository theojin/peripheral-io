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

#include "peripheral_io.h"
#include "peripheral_gdbus.h"
#include "peripheral_common.h"
#include "peripheral_io_gdbus.h"

PeripheralIoGdbusAdc *adc_proxy = NULL;

void adc_proxy_init(void)
{
	GError *error = NULL;

	if (adc_proxy != NULL)
		return;

	adc_proxy = peripheral_io_gdbus_adc_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_ADC_PATH,
		NULL,
		&error);
}

void adc_proxy_deinit()
{
	if (adc_proxy) {
		g_object_unref(adc_proxy);
		if (!G_IS_OBJECT(adc_proxy))
			adc_proxy = NULL;
	}
}

int peripheral_gdbus_adc_read(unsigned int device, unsigned int channel, int *data)
{
	GError *error = NULL;
	peripheral_error_e ret = PERIPHERAL_ERROR_NONE;
	gint value;

	if (adc_proxy == NULL) return PERIPHERAL_ERROR_UNKNOWN;

	if (peripheral_io_gdbus_adc_call_read_sync(
			adc_proxy,
			device,
			channel,
			&value,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Error in %s() : %s", __func__, error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_UNKNOWN;
	}

	*data = value;

	return ret;
}
