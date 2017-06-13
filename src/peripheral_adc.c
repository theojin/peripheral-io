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
#include "peripheral_gdbus_adc.h"
#include "peripheral_common.h"

int peripheral_adc_read(unsigned int device, unsigned int channel, int *data)
{
	int ret;

	adc_proxy_init();

	ret = peripheral_gdbus_adc_read(device, channel, data);
	if (ret != PERIPHERAL_ERROR_NONE)
		_E("Failed to read, ret : %d", ret);

	return ret;
}
