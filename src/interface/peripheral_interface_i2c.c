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

#include <sys/ioctl.h>

#include "peripheral_interface_i2c.h"

#define MAX_ERR_LEN 255

int peripheral_interface_i2c_close(peripheral_i2c_h i2c)
{
	int status;

	_D("fd : %d", i2c->fd);
	RETVM_IF(i2c->fd < 0, -EINVAL, "Invalid fd");

	status = close(i2c->fd);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_i2c_read(peripheral_i2c_h i2c, uint8_t *data, uint32_t length)
{
	int status;

	RETVM_IF(i2c->fd < 0, -EINVAL, "Invalid fd : %d", i2c->fd);

	status = read(i2c->fd, data, length);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_i2c_write(peripheral_i2c_h i2c, uint8_t *data, uint32_t length)
{
	int status;

	RETVM_IF(i2c->fd < 0, -EINVAL, "Invalid fd : %d", i2c->fd);

	status = write(i2c->fd, data, length);
	CHECK_ERROR(status);

	return 0;
}

int peripheral_interface_i2c_smbus_ioctl(peripheral_i2c_h i2c, struct i2c_smbus_ioctl_data *data)
{
	int status;

	RETVM_IF(i2c->fd < 0, -EINVAL, "Invalid fd : %d", i2c->fd);

	status = ioctl(i2c->fd, I2C_SMBUS, data);
	CHECK_ERROR(status);

	return 0;
}
