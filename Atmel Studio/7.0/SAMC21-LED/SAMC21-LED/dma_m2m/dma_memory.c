/**
 * \file
 *
 * \brief Memory with DMA functionality implementation.
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

#include "dma_memory.h"
#include "dma_memory_config.h"
#include <utils_assert.h>
#include <utils.h>
#include <hal_atomic.h>
#include <hpl_dma.h>
/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

/**
 * \brief memory with dma descriptor instance
 */
static struct dma_memory_descriptor descr;

/**
 * \internal Process transfer done interrupts
 *
 * \param[in] resource The pointer to memory resource
 */
static void dma_transfer_done(struct _dma_resource *resource)
{
	(void)resource;
	if (descr.memory_cb.complete) {
		descr.memory_cb.complete();
	}
}

/**
 * \internal Process transfer error interrupts
 *
 * \param[in] resource The pointer to memory resource
 */
static void dma_memory_error(struct _dma_resource *resource)
{
	(void)resource;
	if (descr.memory_cb.error) {
		descr.memory_cb.error();
	}
}
int32_t _dma_get_channel_resource(struct _dma_resource **resource, const uint8_t channel);
/**
 * \brief Initialize DMA
 */
int32_t dma_memory_init(void)
{   
//	_dma_get_channel_resource(&descr.resource, CONF_DMA_MEMORY_CHANNEL);
	descr.resource->dma_cb.transfer_done = dma_transfer_done;
	descr.resource->dma_cb.error         = dma_memory_error;

	return ERR_NONE;
}

/**
 * \brief Register DMA callback
 */
int32_t dma_memory_register_callback(const enum dma_memory_callback_type type, dma_memory_cb_t cb)
{
	switch (type) {
	case DMA_MEMORY_COMPLETE_CB:
		descr.memory_cb.complete = cb;
		break;

	case DMA_MEMORY_ERROR_CB:
		descr.memory_cb.error = cb;
		break;

	default:
		return ERR_INVALID_ARG;
	}

	_dma_set_irq_state(CONF_DMA_MEMORY_CHANNEL, (enum _dma_callback_type)type, (cb != NULL));

	return ERR_NONE;
}

/**
 * \brief Memory copy with dma
 */
int32_t dma_memcpy(void *dst, void *src, uint32_t size)
{
	_dma_srcinc_enable(CONF_DMA_MEMORY_CHANNEL, true);
	_dma_set_destination_address(CONF_DMA_MEMORY_CHANNEL, dst);
	_dma_set_source_address(CONF_DMA_MEMORY_CHANNEL, src);
	_dma_set_data_amount(CONF_DMA_MEMORY_CHANNEL, size);
	_dma_enable_transaction(CONF_DMA_MEMORY_CHANNEL, true);

	return ERR_NONE;
}

/**
 * \brief Memory set with dma
 */
int32_t dma_memset(void *dst, int32_t ch, uint32_t size)
{
	static int32_t tmp_ch;

	tmp_ch = ch;

	_dma_set_source_address(CONF_DMA_MEMORY_CHANNEL, &tmp_ch);
	_dma_srcinc_enable(CONF_DMA_MEMORY_CHANNEL, false);
	_dma_set_destination_address(CONF_DMA_MEMORY_CHANNEL, dst);
	_dma_set_data_amount(CONF_DMA_MEMORY_CHANNEL, size);
	_dma_enable_transaction(CONF_DMA_MEMORY_CHANNEL, true);

	return ERR_NONE;
}
