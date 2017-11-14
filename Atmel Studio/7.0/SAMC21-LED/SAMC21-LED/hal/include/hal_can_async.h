/**
 * \file
 *
 * \brief Control Area Network(CAN) functionality declaration.
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

#ifndef HAL_CAN_ASYNC_H_INCLUDED
#define HAL_CAN_ASYNC_H_INCLUDED

#include <hpl_can.h>
#include <hpl_can_async.h>
#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \addtogroup doc_driver_hal_can_async
 *
 *@{
 */

/**
 * \brief CAN Asynchronous descriptor
 *
 * The CAN descriptor forward declaration.
 */
struct can_async_descriptor;

/**
 * Callback for CAN interrupt
 */
typedef void (*can_cb_t)(struct can_async_descriptor *const descr);

/**
 * \brief CAN callbacks
 */
struct can_callbacks {
	can_cb_t tx_done;
	can_cb_t rx_done;
	void (*irq_handler)(struct can_async_descriptor *const descr, enum can_async_interrupt_type type);
};

/**
 * \brief CAN descriptor
 */
struct can_async_descriptor {
	struct _can_async_device dev; /*!< CAN HPL device descriptor */
	struct can_callbacks     cb;  /*!< CAN Interrupt Callbacks handler */
};

/**
 * \brief Initialize CAN.
 *
 * This function initializes the given CAN descriptor.
 *
 * \param[in, out] descr A CAN descriptor to initialize.
 * \param[in]      hw    The pointer to hardware instance.
 *
 * \return Initialization status.
 */
int32_t can_async_init(struct can_async_descriptor *const descr, void *const hw);

/**
 * \brief Deinitialize CAN.
 *
 * This function deinitializes the given CAN descriptor.
 *
 * \param[in, out] descr The CAN descriptor to deinitialize.
 *
 * \return De-initialization status.
 */
int32_t can_async_deinit(struct can_async_descriptor *const descr);

/**
 * \brief Enable CAN
 *
 * This function enables CAN by the given can descriptor.
 *
 * \param[in] descr The CAN descriptor to enable.
 *
 * \return Enabling status.
 */
int32_t can_async_enable(struct can_async_descriptor *const descr);

/**
 * \brief Disable CAN
 *
 * This function disables CAN by the given can descriptor.
 *
 * \param[in] descr The CAN descriptor to disable.
 *
 * \return Disabling status.
 */
int32_t can_async_disable(struct can_async_descriptor *const descr);

/**
 * \brief Read a CAN message
 *
 * \param[in] descr The CAN descriptor to read message.
 * \param[in] msg   The CAN message to read to.
 *
 * \return The status of read message.
 */
int32_t can_async_read(struct can_async_descriptor *const descr, struct can_message *msg);

/**
 * \brief Write a CAN message
 *
 * \param[in] descr The CAN descriptor to write message.
 * \param[in] msg   The CAN message to write.
 *
 * \return The status of write message.
 */
int32_t can_async_write(struct can_async_descriptor *const descr, struct can_message *msg);

/**
 * \brief Register CAN callback function to interrupt
 *
 * \param[in] descr The CAN descriptor
 * \param[in] type  Callback type
 * \param[in] cb    A callback function, passing NULL will de-register any
 *                  registered callback
 *
 * \return The status of callback assignment.
 */
int32_t can_async_register_callback(struct can_async_descriptor *const descr, enum can_async_callback_type type,
                                    FUNC_PTR cb);

/**
 * \brief Return number of read errors
 *
 * This function returns the number of read errors.
 *
 * \param[in] descr The CAN descriptor pointer
 *
 * \return The number of read errors.
 */
uint8_t can_async_get_rxerr(struct can_async_descriptor *const descr);

/**
 * \brief Return number of write errors
 *
 * This function returns the number of write errors.
 *
 * \param[in] descr The CAN descriptor pointer
 *
 * \return The number of write errors.
 */
uint8_t can_async_get_txerr(struct can_async_descriptor *const descr);

/**
 * \brief Set CAN to the specified mode
 *
 * This function sets CAN to a specified mode.
 *
 * \param[in] descr The CAN descriptor pointer
 * \param[in] mode  The CAN operation mode
 *
 * \return Status of the operation.
 */
int32_t can_async_set_mode(struct can_async_descriptor *const descr, enum can_mode mode);

/**
 * \brief Set CAN Filter
 *
 * This function sets CAN to a specified mode.
 *
 * \param[in] descr The CAN descriptor pointer
 * \param[in] index   Index of Filter list
 * \param[in] fmt     CAN Indentify Type
 * \param[in] filter  CAN Filter struct, NULL for clear filter
 *
 * \return Status of the operation.
 */
int32_t can_async_set_filter(struct can_async_descriptor *const descr, uint8_t index, enum can_format fmt,
                             struct can_filter *filter);

/**
 * \brief Retrieve the current driver version
 *
 * \return The current driver version.
 */
uint32_t can_async_get_version(void);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* HAL_CAN_ASYNC_H_INCLUDED */
