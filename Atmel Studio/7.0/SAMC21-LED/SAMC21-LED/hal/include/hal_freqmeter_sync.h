/**
 * \file
 *
 * \brief Frequency meter related functionality declaration.
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
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

#ifndef _HAL_FREQ_METER_SYNC_H_INCLUDED
#define _HAL_FREQ_METER_SYNC_H_INCLUDED

#include <hpl_freqmeter_sync.h>

/**
 * \addtogroup doc_driver_hal_freqmeter_sync
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Synchronous frequency meter descriptor
 */
struct freqmeter_sync_descriptor {
	uint32_t                      period;
	enum freqmeter_parameter      param;
	struct _freqmeter_sync_device device;
};

/**
 * \brief Initialize the frequency meter
 *
 * \param[out] descr The pointer to the frequency meter descriptor
 * \param[in] hw The pointer to the hardware instance
 *
 * \return Initialization status.
 */
int32_t freqmeter_sync_init(struct freqmeter_sync_descriptor *const descr, void *const hw);

/**
 * \brief Deinitialize the frequency meter
 *
 * \param[in] descr The pointer to the frequency meter descriptor
 *
 * \return De-initialization status.
 */
int32_t freqmeter_sync_deinit(struct freqmeter_sync_descriptor *const descr);

/**
 * \brief Enable the frequency meter
 *
 * \param[in] descr The pointer to the frequency meter descriptor
 *
 * \return Enabling status.
 */
int32_t freqmeter_sync_enable(struct freqmeter_sync_descriptor *const descr);

/**
 * \brief Disable the frequency meter
 *
 * \param[in] descr The pointer to the frequency meter descriptor
 *
 * \return Disabling status.
 */
int32_t freqmeter_sync_disable(struct freqmeter_sync_descriptor *const descr);

/**
 * \brief Set period of measurement
 *
 * \param[in] descr The pointer to the frequency meter descriptor
 * \param[in] period Period in microseconds
 *
 * \return Status for period setting
 */
int32_t freqmeter_sync_set_measurement_period(struct freqmeter_sync_descriptor *const descr, const uint32_t period);

/**
 * \brief Set the parameter to measure
 *
 * \param[in] descr The pointer to the frequency meter descriptor
 * \param[in] parameter Signal parameter to measure
 *
 * \return Status for the parameter setting
 */
int32_t freqmeter_sync_set_measurement_parameter(struct freqmeter_sync_descriptor *const descr,
                                                 const enum freqmeter_parameter          parameter);

/**
 * \brief Read values from the frequency meter
 *
 * \param[in] descr  The pointer to the frequency meter descriptor
 * \param[in] data   The point to the data buffer to write data to
 * \param[in] length The amount of measurements to read
 *
 * \return Amount of bytes to read
 */
int32_t freqmeter_sync_read(struct freqmeter_sync_descriptor *const descr, uint32_t *const data, const uint16_t length);

/**
 * \brief Retrieve the current driver version
 *
 * \return Current driver version.
 */
uint32_t freqmeter_sync_get_version(void);

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HAL_FREQ_METER_SYNC_H_INCLUDED */
