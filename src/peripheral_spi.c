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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

peripheral_spi_context_h peripheral_spi_open(unsigned int bus, peripheral_spi_context_h config)
{
	return NULL;
}

int	peripheral_spi_write(peripheral_spi_context_h hnd, char *txbuf, int length)
{
	return PERIPHERAL_ERROR_INVALID_OPERATION;
}

int	peripheral_spi_recv(peripheral_spi_context_h hnd, char *rxbuf, int length)
{
	return PERIPHERAL_ERROR_INVALID_OPERATION;
}

int peripheral_spi_transfer_buf(peripheral_spi_context_h hnd, char *txbuf, char *rxbuf, int length)
{
	return PERIPHERAL_ERROR_INVALID_OPERATION;
}

int	peripheral_spi_close(peripheral_spi_context_h hnd)
{
	return PERIPHERAL_ERROR_INVALID_OPERATION;
}
