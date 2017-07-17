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

/* Userspace driver for MMA7455 Accelerometer */

#define MMA7455_ADDRESS 0x1D //I2C Address of MMA7455

#define MMA7455_MCTL 0x16 // Mode Control(register)
#define MMA7455_MCTL_STANDBY_MODE 0x0 // [1:0] Standby mode
#define MMA7455_MCTL_MEASUREMENT_MODE 0x01 // [1:0] Measurement mode
#define MMA7455_MCTL_LEVEL_DETECTION_MODE 0x02 // [1:0] Level detection mode
#define MMA7455_MCTL_PULSE_DETECTION_MODE 0x03 // [1:0] Pulse detection mode
#define MMA7455_MCTL_2G 0x04 // [3:2] Set Sensitivity to 2g
#define MMA7455_MCTL_4G 0x08 // [3:2] Set Sensitivity to 4g
#define MMA7455_MCTL_8G 0x00 // [3:2] Set Sensitivity to 8g
#define MMA7455_MCTL_STON 0x10 // Self-test is enabled
#define MMA7455_MCTL_SPI3W 0x20 // SPI is 3 wire mode
#define MMA7455_MCTL_DRPD 0x40 // Data ready status is not output to INT1/DRDY PIN

#define MMA7455_INTRST 0x17 // Interrupt latch reset(register)
#define MMA7455_INTRST_CLRINT 0x03
#define MMA7445_INTRST_DONOTCLR 0x00

#define MMA7455_XOUT8 0x06 // 8 bits output value X (register)
#define MMA7455_YOUT8 0x07 // 8 bits output value Y (register)
#define MMA7455_ZOUT8 0x08 // 8 bits output value Z (register)

#define MMA7455_SPI_REGISTER_WRITE 0x80

typedef struct {
	uint8_t x_pos;
	uint8_t y_pos;
	uint8_t z_pos;
} mma7455_axes;

int mma7455_i2c_init(int bus_num);
int mma7455_i2c_close();
int mma7455_i2c_reset_isr();
int mma7455_i2c_get_measurement_1(mma7455_axes *result);
int mma7455_i2c_get_measurement_2(mma7455_axes *result);
int mma7455_i2c_get_measurement_3(mma7455_axes *result);
int mma7455_i2c_register_isr(const int gpio_num, gpio_isr_cb cb_func);
int mma7455_i2c_unregister_isr();

int mma7455_spi_init(int bus_num, int cs_num);
int mma7455_spi_close();
int mma7455_spi_get_measurement(mma7455_axes *result);
