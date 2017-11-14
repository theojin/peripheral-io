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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "peripheral_interface_i2c.h"
#include "peripheral_common.h"
#include "peripheral_internal.h"

#define MAX_ERR_LEN 255

int peripheral_interface_i2c_close(peripheral_i2c_h i2c)
{
	int status;

	_D("fd : %d", i2c->fd);
	RETVM_IF(i2c->fd < 0, -EINVAL, "Invalid fd");

	status = close(i2c->fd);
	if (status < 0) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("Failed to close fd : %d", i2c->fd);
		return -EIO;
	}

	return 0;
}

int peripheral_interface_i2c_read(peripheral_i2c_h i2c, uint8_t *data, uint32_t length)
{
	int status;

	RETVM_IF(i2c->fd < 0, -EINVAL, "Invalid fd : %d", i2c->fd);

	status = read(i2c->fd, data, length);
	if (status != length) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("i2c read failed, fd : %d, errmsg : %s", i2c->fd, errmsg);
		return -EIO;
	}

	return 0;
}

int peripheral_interface_i2c_write(peripheral_i2c_h i2c, uint8_t *data, uint32_t length)
{
	int status;

	RETVM_IF(i2c->fd < 0, -EINVAL, "Invalid fd : %d", i2c->fd);

	status = write(i2c->fd, data, length);
	if (status != length) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("i2c write failed fd : %d, errmsg : %s", i2c->fd, errmsg);
		return -EIO;
	}

	return 0;
}

int peripheral_interface_i2c_smbus_ioctl(peripheral_i2c_h i2c, struct i2c_smbus_ioctl_data *data)
{
	int status;

	RETVM_IF(i2c->fd < 0, -EINVAL, "Invalid fd : %d", i2c->fd);

	status = ioctl(i2c->fd, I2C_SMBUS, data);
	if (status < 0) {
		char errmsg[MAX_ERR_LEN];
		strerror_r(errno, errmsg, MAX_ERR_LEN);
		_E("i2c transaction failed fd : %d, errmsg : %s", i2c->fd, errmsg);
		return -EIO;
	}

	return 0;
}
