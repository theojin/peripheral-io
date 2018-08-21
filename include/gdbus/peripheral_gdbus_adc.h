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

#ifndef __PERIPHERAL_GDBUS_ADC_H__
#define __PERIPHERAL_GDBUS_ADC_H__

#include "peripheral_gdbus_common.h"

int peripheral_gdbus_adc_open(peripheral_adc_h adc, int device, int channel);
int peripheral_gdbus_adc_close(peripheral_adc_h adc);

#endif /* __PERIPHERAL_GDBUS_ADC_H__ */
