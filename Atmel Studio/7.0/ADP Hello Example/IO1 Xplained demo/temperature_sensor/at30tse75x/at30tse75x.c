/**
 * \file
 *
 * \brief AT30TSE75X driver
 *
 * Copyright (c) 2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <at30tse75x.h>
#include <hal_i2c_m_sync.h>
#include <temperature_sensor.h>
#include <at30tse75x_config.h>

/** Register addresses of at30tse75x */
#define AT30TSE_TEMPERATURE_REG 0
#define AT30TSE_CONFIGURATION_REG 1

/** Register types of at30tse75x */
#define AT30TSE_NON_VOLATILE_REG_TYPE 0

/** Address of temperature sensor */
#define AT30TSE_SENSOR_ADDRESS 0x4F

/** Offset of resolution bit-field */
#define AT30TSE_CONFIGURATION_REG_RESOLUTION_BF_OFFSET 13

/** AT30TSE75x temperature sensor's interface */
static const struct temperature_sensor_interface at30tse75x_interface = {at30tse75x_read};

/**
 * \brief Construct at30tse75x temperature sensor
 */
struct temperature_sensor *at30tse75x_construct(struct temperature_sensor *const me, void *const io,
                                                const uint8_t resolution)
{
	uint8_t                 data[3];
	struct i2c_m_sync_desc *descr;
	struct at30tse75x *     at30 = (struct at30tse75x *)me;

	temperature_sensor_construct(me, io, &at30tse75x_interface);
	descr            = (struct i2c_m_sync_desc *)(me->io);
	at30->resolution = resolution;

	data[0] = AT30TSE_CONFIGURATION_REG | AT30TSE_NON_VOLATILE_REG_TYPE;
	data[1] = (uint16_t)(at30->resolution) << (AT30TSE_CONFIGURATION_REG_RESOLUTION_BF_OFFSET - 8);
	data[2] = 0;
	i2c_m_sync_set_slaveaddr(descr, AT30TSE_SENSOR_ADDRESS, I2C_M_SEVEN);
	io_write(&descr->io, data, 3);

	return me;
}

/**
 * \brief Read temperature from the given sensor
 */
float at30tse75x_read(const struct temperature_sensor *const me)
{
	uint8_t                 buffer[2];
	struct at30tse75x *     at30  = (struct at30tse75x *)me;
	struct i2c_m_sync_desc *descr = (struct i2c_m_sync_desc *)(me->io);
	uint16_t                data;
	int8_t                  sign = 1;

	/* Read the 16-bit temperature register. */
	buffer[0] = AT30TSE_TEMPERATURE_REG | AT30TSE_NON_VOLATILE_REG_TYPE;
	buffer[1] = 0;
	i2c_m_sync_set_slaveaddr(descr, AT30TSE_SENSOR_ADDRESS, I2C_M_SEVEN);
	io_write(&descr->io, buffer, 1);
	io_read(&descr->io, buffer, 2);

	data = (buffer[0] << 8) | buffer[1];
	sign -= (bool)(data & (1 << 15)) << 1;
	data &= ~(1 << 15);

	/* Convert to temperature */
	data = data >> (7 - at30->resolution);
	return (float)data * sign * (0.5 / (1 << at30->resolution));
}
