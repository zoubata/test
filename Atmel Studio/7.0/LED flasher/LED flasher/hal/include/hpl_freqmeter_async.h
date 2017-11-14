/**
 * \file
 *
 * \brief Frequency meter related functionality declaration.
 *
 * Copyright (C) 2015-2016 Atmel Corporation. All rights reserved.
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

#ifndef _HPL_FREQMETER_ASYNC_H_INCLUDED
#define _HPL_FREQMETER_ASYNC_H_INCLUDED

/**
 * \addtogroup HPL Frequency meter
 *
 * \section hpl_freqmeter_async_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#include <hpl_irq.h>
#include <hpl_freqmeter.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Frequency meter device structure
 *
 * The Frequency meter device structure forward declaration.
 */
struct _freqmeter_async_device;

/**
 * \brief Frequency meter callback types
 */
enum _freqmeter_dev_async_callback_type { FREQMETER_DEV_ASYNC_MEASUREMENET_DONE_CB };

/**
 * \brief Frequency meter interrupt callbacks
 */
struct _freqmeter_async_callbacks {
	void (*done)(struct _freqmeter_async_device *device, const uint32_t data);
};

/**
 * \brief Frequency meter device structure
 */
struct _freqmeter_async_device {
	struct _irq_descriptor            irq;
	struct _freqmeter_async_callbacks cbs;
	void *                            hw;
};

/**
 * \name HPL functions
 */
//@{
/**
 * \brief Initialize synchronous frequency meter
 *
 * This function does low level frequency meter configuration.
 *
 * \param[in] device The pointer to frequency meter device instance
 * \param[in] hw The pointer to hardware instance
 *
 * \return Initialization status
 */
int32_t _freqmeter_async_init(struct _freqmeter_async_device *const device, void *const hw);

/**
 * \brief Deinitialize frequency meter
 *
 * This function closes the given frequency meter by disabling its clock.
 *
 * \param[in] device The pointer to frequency meter device instance
 */
void _freqmeter_async_deinit(struct _freqmeter_async_device *const device);

/**
 * \brief Enable frequency meter module
 *
 * This function will enable the frequency meter module
 *
 * \param[in] device The pointer to frequency meter device instance
 */
void _freqmeter_async_enable(struct _freqmeter_async_device *const device);

/**
 * \brief Disable frequency meter module
 *
 * This function will disable the frequency meter module
 *
 * \param[in] device The pointer to frequency meter device instance
 */
void _freqmeter_async_disable(struct _freqmeter_async_device *const device);

/**
 * \brief Start frequency meter module
 *
 * \param[in] device The pointer to frequency meter device instance
 */
void _freqmeter_async_start(struct _freqmeter_async_device *const device);

/**
 * \brief Set measurement period
 *
 * \param[in] device The pointer to frequency meter device instance
 * \param[in] period The period to set, in ms
 *
 * \return The period value which is set
 */
uint32_t _freqmeter_async_set_measurement_period(struct _freqmeter_async_device *const device, const uint32_t period);

/**
 * \brief Read values from frequency meter
 *
 *
 * \param[in] descr The pointer to frequency meter descriptor
 * \param[in] data The point to data buffer to write data to
 * \param[in] length The amount of measurement to read
 *
 * \return Amount of bytes read
 */
uint32_t _freqmeter_async_read(const struct _freqmeter_async_device *const device, uint32_t *const data,
                               const uint16_t length);

/**
 * \brief Enable/disable frequency meter interrupt
 *
 * param[in] device The pointer to ADC device instance
 * param[in] type The type of interrupt to disable/enable if applicable
 * param[in] state Enable or disable
 */
void _freqmeter_async_set_irq_state(struct _freqmeter_async_device *const         device,
                                    const enum _freqmeter_dev_async_callback_type type, const bool state);

//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_FREQMETER_ASYNC_H_INCLUDED */
