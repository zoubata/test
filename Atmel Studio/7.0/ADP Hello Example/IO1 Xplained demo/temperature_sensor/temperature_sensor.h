/**
 * \file
 *
 * \brief Temperature Sensor declaration.
 *
 * Copyright (C) 2016 Atmel Corporation. All rights reserved.
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

#ifndef _TEMPERATURE_SENSOR_H_INCLUDED
#define _TEMPERATURE_SENSOR_H_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Forward declaration of temperature sensor structure. */
struct temperature_sensor;

/**
 * \brief Interface of abstract temperature sensor
 */
struct temperature_sensor_interface {
	float (*read)(const struct temperature_sensor *const me);
};

/**
 * \brief Abstract temperature sensor
 */
struct temperature_sensor {
	/** The pointer to interface used to communicate with temperature sensor */
	void *io;
	/** The interface of abstract temperature sensor */
	const struct temperature_sensor_interface *interface;
};

/**
 * \brief Construct abstract temperature sensor
 *
 * \param[in] me The pointer to temperature sensor to initialize
 * \param[in] io The pointer to instance of interface to actual sensor
 * \param[in] interface The pointer to interface of temperature sensor
 *
 * \return pointer to initialized sensor
 */
struct temperature_sensor *temperature_sensor_construct(struct temperature_sensor *const me, void *const io,
                                                        const struct temperature_sensor_interface *const interface);

/**
 * \brief Read temperature from the given sensor
 *
 * \param[in] me The pointer to temperature sensor to read temperature from
 *
 * \return temperature
 */
float temperature_sensor_read(const struct temperature_sensor *const me);

#ifdef __cplusplus
}
#endif

#endif /* _TEMPERATURE_SENSOR_H_INCLUDED */
