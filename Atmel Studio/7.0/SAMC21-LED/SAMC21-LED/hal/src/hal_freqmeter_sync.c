/**
 * \file
 *
 * \brief Frequency meter  related functionality implementation.
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

#include <hal_freqmeter_sync.h>
#include <utils_assert.h>

/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

/**
 * \brief Initialize frequency meter
 */
int32_t freqmeter_sync_init(struct freqmeter_sync_descriptor *const descr, void *const hw)
{
	int32_t status;

	ASSERT(descr && hw);

	status = _freqmeter_sync_init(&descr->device, hw);
	if (status) {
		return status;
	}

	descr->period = _freqmeter_sync_set_measurement_period(&descr->device, 0xFFFFFFFF);

	return ERR_NONE;
}

/**
 * \brief Deinitialize frequency meter
 */
int32_t freqmeter_sync_deinit(struct freqmeter_sync_descriptor *const descr)
{
	ASSERT(descr);

	_freqmeter_sync_deinit(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Enable frequency meter
 */
int32_t freqmeter_sync_enable(struct freqmeter_sync_descriptor *const descr)
{
	ASSERT(descr);

	_freqmeter_sync_enable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Disable frequency meter
 */
int32_t freqmeter_sync_disable(struct freqmeter_sync_descriptor *const descr)
{
	ASSERT(descr);

	_freqmeter_sync_disable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Set period of measurement
 */
int32_t freqmeter_sync_set_measurement_period(struct freqmeter_sync_descriptor *const descr, const uint32_t period)
{
	ASSERT(descr && period);

	descr->period = _freqmeter_sync_set_measurement_period(&descr->device, period);

	return ERR_NONE;
}

/**
 * \brief Set parameter to measure
 */
int32_t freqmeter_sync_set_measurement_parameter(struct freqmeter_sync_descriptor *const descr,
                                                 const enum freqmeter_parameter          parameter)
{
	ASSERT(descr);

	descr->param = parameter;

	return ERR_NONE;
}

/**
 * \brief Read values from frequency meter
 */
int32_t freqmeter_sync_read(struct freqmeter_sync_descriptor *const descr, uint32_t *const data, const uint16_t length)
{
	uint32_t raw_result;
	uint16_t offset = 0;

	ASSERT(descr && data && length);

	do {
		_freqmeter_sync_start(&descr->device);
		while (!_freqmeter_sync_is_measurement_done(&descr->device))
			;

		raw_result = _freqmeter_sync_read(&descr->device);
		if (FREQMETER_FREQUENCY == descr->param) {
			data[offset] = (uint32_t)((uint64_t)raw_result * 1000000 / descr->period);
		} else {
			data[offset] = (uint32_t)((uint64_t)descr->period * 1000 / raw_result);
		}
		offset++;
	} while (offset < length);

	return length;
}

/**
 * \brief Retrieve the current driver version
 */
uint32_t freqmeter_sync_get_version(void)
{
	return DRIVER_VERSION;
}
