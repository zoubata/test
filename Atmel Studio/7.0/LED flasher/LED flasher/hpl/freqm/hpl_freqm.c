/**
 * \file
 *
 * \brief SAM Frequency Meter
 *
 * Copyright (C) 2015 - 2017 Atmel Corporation. All rights reserved.
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

#include <hpl_freqm_config.h>
#include <hpl_freqmeter_sync.h>
#include <hpl_freqmeter_async.h>
#include <peripheral_clk_config.h>
#include <utils_assert.h>

/*!< Pointer to hpl device */
static struct _freqmeter_async_device *_freq_dev = NULL;

static int32_t _freqmeter_init(void *const hw);
static inline void _freqmeter_deinit(void *const hw);
static uint32_t _freqmeter_set_measurement_period(void *const hw, const uint32_t period);

/**
 * \brief Initialize synchronous frequency meter
 */
int32_t _freqmeter_sync_init(struct _freqmeter_sync_device *const device, void *const hw)
{
	ASSERT(device);

	device->hw = hw;

	return _freqmeter_init(device->hw);
}

/**
 * \brief Initialize asynchronous frequency meter
 */
int32_t _freqmeter_async_init(struct _freqmeter_async_device *const device, void *const hw)
{
	int32_t init_status;

	ASSERT(device);

	init_status = _freqmeter_init(hw);
	if (init_status) {
		return init_status;
	}
	device->hw = hw;
	_freq_dev  = device;

	NVIC_DisableIRQ(FREQM_IRQn);
	NVIC_ClearPendingIRQ(FREQM_IRQn);
	NVIC_EnableIRQ(FREQM_IRQn);

	return ERR_NONE;
}

/**
 * \brief De-initialize frequency meter
 */
void _freqmeter_sync_deinit(struct _freqmeter_sync_device *const device)
{
	_freqmeter_deinit(device->hw);
}

/**
 * \brief De-initialize frequency meter
 */
void _freqmeter_async_deinit(struct _freqmeter_async_device *const device)
{
	NVIC_DisableIRQ(FREQM_IRQn);
	NVIC_ClearPendingIRQ(FREQM_IRQn);

	_freqmeter_deinit(device->hw);
}

/**
 * \brief Enable frequency meter module
 */
void _freqmeter_sync_enable(struct _freqmeter_sync_device *const device)
{
	hri_freqm_set_CTRLA_ENABLE_bit(device->hw);
	hri_freqm_wait_for_sync(device->hw, FREQM_SYNCBUSY_ENABLE);
}

/**
 * \brief Enable frequency meter module
 */
void _freqmeter_async_enable(struct _freqmeter_async_device *const device)
{
	hri_freqm_set_CTRLA_ENABLE_bit(device->hw);
	hri_freqm_wait_for_sync(device->hw, FREQM_SYNCBUSY_ENABLE);
}

/**
 * \brief Disable frequency meter module
 */
void _freqmeter_sync_disable(struct _freqmeter_sync_device *const device)
{
	hri_freqm_clear_CTRLA_ENABLE_bit(device->hw);
	hri_freqm_wait_for_sync(device->hw, FREQM_SYNCBUSY_ENABLE);
}

/**
 * \brief Disable frequency meter module
 */
void _freqmeter_async_disable(struct _freqmeter_async_device *const device)
{
	hri_freqm_clear_CTRLA_ENABLE_bit(device->hw);
	hri_freqm_wait_for_sync(device->hw, FREQM_SYNCBUSY_ENABLE);
}

/**
 * \brief Start frequency meter module
 */
void _freqmeter_sync_start(struct _freqmeter_sync_device *const device)
{
	hri_freqm_write_CTRLB_reg(device->hw, FREQM_CTRLB_START);
}

/**
 * \brief Start frequency meter module
 */
void _freqmeter_async_start(struct _freqmeter_async_device *const device)
{
	hri_freqm_write_CTRLB_reg(device->hw, FREQM_CTRLB_START);
}

/**
 * \brief Set measurement period
 */
uint32_t _freqmeter_sync_set_measurement_period(struct _freqmeter_sync_device *const device, const uint32_t period)
{
	return _freqmeter_set_measurement_period(device->hw, period);
}

/**
 * \brief Set measurement period
 */
uint32_t _freqmeter_async_set_measurement_period(struct _freqmeter_async_device *const device, const uint32_t period)
{
	return _freqmeter_set_measurement_period(device->hw, period);
}

/**
 * \brief Check if measurement is complete
 *
 * \param[in] device The pointer to frequency meter device instance
 *
 * \return True if it is complete, false otherwise
 */
bool _freqmeter_sync_is_measurement_done(const struct _freqmeter_sync_device *const device)
{
	return !hri_freqm_get_STATUS_BUSY_bit(device->hw);
}

/**
 * \brief Read values from frequency meter
 */
uint32_t _freqmeter_sync_read(const struct _freqmeter_sync_device *const device)
{
	return hri_freqm_read_VALUE_reg(device->hw);
}

/**
 * \brief Enable/disable frequency meter interrupt
 */
void _freqmeter_async_set_irq_state(struct _freqmeter_async_device *const         device,
                                    const enum _freqmeter_dev_async_callback_type type, const bool state)
{
	void *const hw = device->hw;

	if (FREQMETER_DEV_ASYNC_MEASUREMENET_DONE_CB == type) {
		hri_freqm_write_INTEN_DONE_bit(hw, state);
	}
}

/**
 * \brief Initialize frequency meter
 *
 * \param[in] hw The pointer to hardware instance
 *
 * \return Initialization status
 */
static int32_t _freqmeter_init(void *const hw)
{
	if (hri_freqm_get_CTRLA_ENABLE_bit(hw)) {
		return ERR_DENIED;
	}
	hri_freqm_write_CFGA_reg(hw, CONF_FREQM_REFNUM);

	return ERR_NONE;
}

/**
 * \brief De-initialize frequency meter
 *
 * \param[in] hw The pointer to hardware instance
 */
static inline void _freqmeter_deinit(void *const hw)
{
	hri_freqm_clear_CTRLA_ENABLE_bit(hw);
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_ENABLE);
	hri_freqm_set_CTRLA_SWRST_bit(hw);
}

/**
 * \brief Set measurement period
 *
 * \param[in] hw The pointer to hardware instance
 * \param[in] period The period to set
 *
 * \return The period value which is set
 */
static uint32_t _freqmeter_set_measurement_period(void *const hw, const uint32_t period)
{
	bool     enabled = hri_freqm_get_CTRLA_ENABLE_bit(hw);
	uint32_t value   = (uint32_t)((uint64_t)period * CONF_GCLK_FREQM_REF_FREQUENCY / 1000000);

	hri_freqm_write_CTRLA_ENABLE_bit(hw, 0);
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_ENABLE);

	if (value > 0xFF) {
		value = CONF_FREQM_REFNUM;
	}
	hri_freqm_write_CFGA_reg(hw, value);

	if (enabled) {
		hri_freqm_write_CTRLA_ENABLE_bit(hw, enabled);
		hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_ENABLE);
	}

	return (value * 1000000) / CONF_GCLK_FREQM_REF_FREQUENCY;
}
