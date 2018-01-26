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

#include "peripheral_interface_adc.h"

void peripheral_interface_adc_close(peripheral_adc_h adc)
{
	close(adc->fd);
}

int peripheral_interface_adc_read(peripheral_adc_h adc, uint32_t *data)
{
	int ret;
	int result;
	char adc_buf[ADC_BUFFER_MAX] = {0, };

	lseek(adc->fd, 0, SEEK_SET);
	ret = read(adc->fd, adc_buf, ADC_BUFFER_MAX);
	CHECK_ERROR(ret <= 0);

	result = atoi(adc_buf);
	*data = result;

	return PERIPHERAL_ERROR_NONE;
}