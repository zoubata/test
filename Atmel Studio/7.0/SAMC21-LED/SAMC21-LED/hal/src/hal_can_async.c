/**
 * \file
 *
 * \brief Control Area Network(CAN) functionality implementation.
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
#include <hal_can_async.h>
#include <utils_assert.h>

#define DRIVER_VERSION 0x00000001u

/**
 * \internal Callback of CAN Message Write finished
 *
 * \param[in] dev The pointer to CAN device structure
 */
static void can_tx_done(struct _can_async_device *dev);
/**
 * \internal Callback of CAN Message Read finished
 *
 * \param[in] dev The pointer to CAN device structure
 */
static void can_rx_done(struct _can_async_device *dev);
/**
 * \internal Callback of CAN Interrupt
 *
 * \param[in] dev  The pointer to CAN device structure
 * \param[in] type Interrupt source type
 */
static void can_irq_handler(struct _can_async_device *dev, enum can_async_interrupt_type type);

/**
 * \brief Initialize CAN.
 */
int32_t can_async_init(struct can_async_descriptor *const descr, void *const hw)
{
	int32_t rc;

	ASSERT(descr && hw);

	rc = _can_async_init(&descr->dev, hw);
	if (rc) {
		return rc;
	}
	descr->dev.cb.tx_done     = can_tx_done;
	descr->dev.cb.rx_done     = can_rx_done;
	descr->dev.cb.irq_handler = can_irq_handler;

	return ERR_NONE;
}

/**
 * \brief Deinitialize CAN.
 */
int32_t can_async_deinit(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_deinit(&descr->dev);
}

/**
 * \brief Enable CAN
 */
int32_t can_async_enable(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_enable(&descr->dev);
}

/**
 * \brief Disable CAN
 */
int32_t can_async_disable(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_disable(&descr->dev);
}

/**
 * \brief Read a CAN message
 */
int32_t can_async_read(struct can_async_descriptor *const descr, struct can_message *msg)
{
	ASSERT(descr && msg);
	return _can_async_read(&descr->dev, msg);
}

/**
 * \brief Write a CAN message
 */
int32_t can_async_write(struct can_async_descriptor *const descr, struct can_message *msg)
{
	ASSERT(descr && msg);
	return _can_async_write(&descr->dev, msg);
}

/**
 * \brief Register CAN callback function to interrupt
 */
int32_t can_async_register_callback(struct can_async_descriptor *const descr, enum can_async_callback_type type,
                                    FUNC_PTR cb)
{
	ASSERT(descr);

	switch (type) {
	case CAN_ASYNC_RX_CB:
		descr->cb.rx_done = (cb != NULL) ? (can_cb_t)cb : NULL;
		break;
	case CAN_ASYNC_TX_CB:
		descr->cb.tx_done = (cb != NULL) ? (can_cb_t)cb : NULL;
		break;
	case CAN_ASYNC_IRQ_CB:
		descr->cb.irq_handler
		    = (cb != NULL) ? (void (*)(struct can_async_descriptor * const, enum can_async_interrupt_type))cb : NULL;
		break;
	default:
		return ERR_INVALID_ARG;
	}

	_can_async_set_irq_state(&descr->dev, type, NULL != cb);

	return ERR_NONE;
}

/**
 * \brief Return number of read errors
 */
uint8_t can_async_get_rxerr(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_get_rxerr(&descr->dev);
}

/**
 * \brief Return number of write errors
 */
uint8_t can_async_get_txerr(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_get_txerr(&descr->dev);
}

/**
 * \brief Set CAN to the specified mode
 */
int32_t can_async_set_mode(struct can_async_descriptor *const descr, enum can_mode mode)
{
	ASSERT(descr);
	return _can_async_set_mode(&descr->dev, mode);
}

/**
 * \brief Set CAN filter
 */
int32_t can_async_set_filter(struct can_async_descriptor *const descr, uint8_t index, enum can_format fmt,
                             struct can_filter *filter)
{
	ASSERT(descr);
	return _can_async_set_filter(&descr->dev, index, fmt, filter);
}

/**
 * \brief Retrieve the current driver version
 */
uint32_t can_async_get_version(void)
{
	return DRIVER_VERSION;
}

/**
 * \internal Callback of CAN Message Write finished
 */
static void can_tx_done(struct _can_async_device *dev)
{
	struct can_async_descriptor *const descr = CONTAINER_OF(dev, struct can_async_descriptor, dev);

	if (descr->cb.tx_done) {
		descr->cb.tx_done(descr);
	}
}

/**
 * \internal Callback of CAN Message Read finished
 */
static void can_rx_done(struct _can_async_device *dev)
{
	struct can_async_descriptor *const descr = CONTAINER_OF(dev, struct can_async_descriptor, dev);

	if (descr->cb.rx_done) {
		descr->cb.rx_done(descr);
	}
}

/**
 * \internal Callback of CAN Interrupt
 */
static void can_irq_handler(struct _can_async_device *dev, enum can_async_interrupt_type type)
{
	struct can_async_descriptor *const descr = CONTAINER_OF(dev, struct can_async_descriptor, dev);

	if (descr->cb.irq_handler) {
		descr->cb.irq_handler(descr, type);
	}
}
