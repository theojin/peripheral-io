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

#ifndef __PERIPHERAL_GDBUS_I2C_H__
#define __PERIPHERAL_GDBUS_I2C_H__

void i2c_proxy_init(void);
void i2c_proxy_deinit(void);

int peripheral_gdbus_i2c_open(peripheral_i2c_h i2c, int bus, int address);
int peripheral_gdbus_i2c_close(peripheral_i2c_h i2c);
int peripheral_gdbus_i2c_read(peripheral_i2c_h i2c, uint8_t *data, int length);
int peripheral_gdbus_i2c_write(peripheral_i2c_h i2c, uint8_t *data, int length);

#endif /* __PERIPHERAL_GDBUS_I2C_H__ */
