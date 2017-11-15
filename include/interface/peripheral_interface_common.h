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

#ifndef __PERIPHERAL_INTERFACE_COMMON_H__
#define __PERIPHERAL_INTERFACE_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "peripheral_io.h"
#include "peripheral_internal.h"
#include "peripheral_common.h"

#define CHECK_ERROR(val) \
	do { \
		if (val < 0) { \
			if (errno == EAGAIN) \
				return -EAGAIN; \
			char errmsg[255]; \
			strerror_r(errno, errmsg, sizeof(errmsg)); \
			_E("Failed the %s(%d) function. errmsg: %s", __FUNCTION__, __LINE__, errmsg); \
			return -EIO; \
		} \
	} while (0)

#endif /*__PERIPHERAL_INTERFACE_COMMON_H__*/