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

#ifndef HPL_CAN_ASYNC_H_INCLUDED
#define HPL_CAN_ASYNC_H_INCLUDED

#include <utils.h>
#include <hpl_can.h>
#include <hpl_irq.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup hpl_can_async CAN HPL Driver
 *
 * \section can_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

/**
 * \brief CAN device descriptor forware declaration
 */
struct _can_async_device;

/**
 * \brief CAN callback types
 */
enum can_async_callback_type {
	CAN_ASYNC_RX_CB, /*!< A new message arrived */
	CAN_ASYNC_TX_CB, /*!< A message transmitted */
	CAN_ASYNC_IRQ_CB /*!< Message error of some kind on the CAN bus IRQ */
};

enum can_async_interrupt_type {
	CAN_IRQ_EW, /*!< Error warning, Error counter has reached the
                  error warning limit of 96, An error count value
                  greater than about 96 indicates a heavily disturbed
                  bus. It may be of advantage to provide means to test
                  for this condition. Refer to ISO 11898-1 (Bosch CAN
                  specification 2.0 part A,B)
                  */
	CAN_IRQ_EA, /*!< Error Active State, The CAN node normally take
                   part in bus communication and sends an ACTIVE ERROR
                   FLAG when an error has been detected.
                   Refer to ISO 11898-1 (7)
                   */
	CAN_IRQ_EP, /*!< Error Passive State, The Can node goes into error
                  passive state if at least one of its error counters is
                  greater than 127. It still takes part in bus
                  activities, but it sends a passive error frame only,
                  on errors. Refer to ISO 11898-1 (7)
                  */
	CAN_IRQ_BO, /*!< Bus Off State, The CAN node is 'bus off' when the
                   TRANSMIT ERROR COUNT is greater than or equal to 256.
                   Refer to ISO 11898-1 (7)
                   */
	CAN_IRQ_DO  /*!< Data Overrun in receive queue. A message was lost
                   because the messages in the queue was not reading and
                   releasing fast enough. There is not enough space for
                   a new message in receive queue.
                   */
};
/**
 * \brief CAN interrupt handlers structure
 */
struct _can_async_callback {
	void (*tx_done)(struct _can_async_device *dev);
	void (*rx_done)(struct _can_async_device *dev);
	void (*irq_handler)(struct _can_async_device *dev, enum can_async_interrupt_type type);
};

/**
 * \brief CAN device descriptor
 */
struct _can_async_device {
	void *                     hw;      /*!< CAN hardware pointer */
	struct _can_async_callback cb;      /*!< CAN interrupt handler */
	struct _irq_descriptor     irq;     /*!< Interrupt descriptor */
	void *                     context; /*!< CAN hardware context */
};

/**
 * \brief Initialize CAN.
 *
 * This function initializes the given CAN device descriptor.
 *
 * \param[in, out] dev   A CAN device descriptor to initialize
 * \param[in]      hw    The pointer to hardware instance
 *
 * \return Initialization status.
 */
int32_t _can_async_init(struct _can_async_device *const dev, void *const hw);

/**
 * \brief Deinitialize CAN.
 *
 * This function deinitializes the given can device descriptor.
 *
 * \param[in] dev The CAN device descriptor to deinitialize
 *
 * \return De-initialization status.
 */
int32_t _can_async_deinit(struct _can_async_device *const dev);

/**
 * \brief Enable CAN
 *
 * This function enable CAN by the given can device descriptor.
 *
 * \param[in] dev The CAN device descriptor to enable
 *
 * \return Enabling status.
 */
int32_t _can_async_enable(struct _can_async_device *const dev);

/**
 * \brief Disable CAN
 *
 * This function disable CAN by the given can device descriptor.
 *
 * \param[in] dev The CAN descriptor to disable
 *
 * \return Disabling status.
 */
int32_t _can_async_disable(struct _can_async_device *const dev);

/**
 * \brief Read a CAN message
 *
 * \param[in] dev   The CAN device descriptor to read message.
 * \param[in] msg   The CAN message to read to.
 *
 * \return The status of read message.
 */
int32_t _can_async_read(struct _can_async_device *const dev, struct can_message *msg);

/**
 * \brief Write a CAN message
 *
 * \param[in] dev   The CAN device descriptor to write message.
 * \param[in] msg   The CAN message to write.
 *
 * \return The status of write message.
 */
int32_t _can_async_write(struct _can_async_device *const dev, struct can_message *msg);

/**
 * \brief Set CAN Interrupt State
 *
 * \param[in] dev   The CAN device descriptor
 * \param[in] type  Callback type
 * \param[in] state ture for enable or false for disable
 *
 */
void _can_async_set_irq_state(struct _can_async_device *const dev, enum can_async_callback_type type, bool state);

/**
 * \brief Return number of read errors
 *
 * This function return number of read errors
 *
 * \param[in] dev The CAN device descriptor pointer
 *
 * \return Number of read errors.
 */
uint8_t _can_async_get_rxerr(struct _can_async_device *const dev);

/**
 * \brief Return number of write errors
 *
 * This function return number of write errors
 *
 * \param[in] dev The CAN device descriptor pointer
 *
 * \return Number of write errors.
 */
uint8_t _can_async_get_txerr(struct _can_async_device *const dev);

/**
 * \brief Set CAN to the specified mode
 *
 * This function set CAN to a specified mode
 *
 * \param[in] dev The CAN device descriptor pointer
 * \param[in] mode  CAN operation mode
 *
 * \return Status of the operation
 */
int32_t _can_async_set_mode(struct _can_async_device *const dev, enum can_mode mode);

/**
 * \brief Set CAN to the specified mode
 *
 * This function set CAN to a specified mode
 *
 * \param[in] dev The CAN device descriptor pointer
 * \param[in] index   Index of Filter list
 * \param[in] filter  CAN Filter struct, NULL for clear filter
 *
 * \return Status of the operation
 */
int32_t _can_async_set_filter(struct _can_async_device *const dev, uint8_t index, enum can_format fmt,
                              struct can_filter *filter);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* HPL_CAN_ASYNC_H_INCLUDED */
