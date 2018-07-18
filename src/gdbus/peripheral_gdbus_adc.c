/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
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

#include "peripheral_gdbus_adc.h"

#define ADC_FD_INDEX 0

static PeripheralIoGdbusAdc *adc_proxy = NULL;

static int __adc_proxy_init(void)
{
	GError *error = NULL;

	if (adc_proxy != NULL) {
		_E("Adc proxy is already created");
		g_object_ref(adc_proxy);
		return PERIPHERAL_ERROR_NONE;
	}

	adc_proxy = peripheral_io_gdbus_adc_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		PERIPHERAL_GDBUS_NAME,
		PERIPHERAL_GDBUS_ADC_PATH,
		NULL,
		&error);

	if (adc_proxy == NULL) {
		_E("Failed to create adc proxy : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_IO_ERROR;
	}

	return PERIPHERAL_ERROR_NONE;
}

static int __adc_proxy_deinit(void)
{
	RETVM_IF(adc_proxy == NULL, PERIPHERAL_ERROR_IO_ERROR, "Adc proxy is NULL");

	g_object_unref(adc_proxy);
	if (!G_IS_OBJECT(adc_proxy))
		adc_proxy = NULL;

	return PERIPHERAL_ERROR_NONE;
}

int peripheral_gdbus_adc_open(peripheral_adc_h adc, int device, int channel)
{
	int ret;
	GError *error = NULL;
	GUnixFDList *fd_list = NULL;

	ret = __adc_proxy_init();
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	if (peripheral_io_gdbus_adc_call_open_sync(
			adc_proxy,
			device,
			channel,
			NULL,
			&adc->handle,
			&ret,
			&fd_list,
			NULL,
			&error) == FALSE) {
		_E("Failed to request daemon to adc open : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_IO_ERROR;
	}

	// TODO : If ret is not PERIPHERAL_ERROR_NONE, fd list it NULL from daemon.
	if (ret != PERIPHERAL_ERROR_NONE)
		return ret;

	adc->fd = g_unix_fd_list_get(fd_list, ADC_FD_INDEX, &error);
	if (adc->fd < 0) {
		_E("Failed to get fd for adc : %s", error->message);
		g_error_free(error);
		ret = PERIPHERAL_ERROR_IO_ERROR;
	}

	g_object_unref(fd_list);

	return ret;
}

int peripheral_gdbus_adc_close(peripheral_adc_h adc)
{
	RETVM_IF(adc_proxy == NULL, PERIPHERAL_ERROR_IO_ERROR, "Adc proxy is NULL");

	int ret;
	GError *error = NULL;

	if (peripheral_io_gdbus_adc_call_close_sync(
			adc_proxy,
			adc->handle,
			&ret,
			NULL,
			&error) == FALSE) {
		_E("Failed to request daemon to adc close : %s", error->message);
		g_error_free(error);
		return PERIPHERAL_ERROR_IO_ERROR;
	}

	__adc_proxy_deinit();

	return ret;
}
