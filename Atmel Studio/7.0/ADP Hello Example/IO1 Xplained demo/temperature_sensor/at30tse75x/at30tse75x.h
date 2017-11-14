/**
 * \file
 *
 * \brief AT30TSE75X temperature declaration
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

#ifndef _AT30TSE75X_H_INCLUDED
#define _AT30TSE75X_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <temperature_sensor.h>

/**
 * \brief AT30TSE75x temperature sensor
 */
struct at30tse75x {
	/** The parent abstract temperature sensor */
	struct temperature_sensor parent;
	/** Resolution used by internal temperature converter */
	uint8_t resolution;
};

/**
 * \brief Construct at30tse75x temperature sensor
 *
 * \param[in] me The pointer to temperature sensor to initialize
 * \param[in] io The pointer to instance of interface to actual sensor
 * \param[in] resolution The resolution of temperature sensor
 *
 * \return pointer to initialized sensor
 */
struct temperature_sensor *at30tse75x_construct(struct temperature_sensor *const me, void *const io,
                                                const uint8_t resolution);

/**
 * \brief Read temperature from the given sensor
 *
 * \param[in] me The pointer to temperature sensor to read temperature from
 *
 * \return temperature
 */
float at30tse75x_read(const struct temperature_sensor *const me);

#ifdef __cplusplus
}
#endif

#endif /* _AT30TSE75X_H_INCLUDED */
