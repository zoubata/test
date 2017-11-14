/**
 * \file
 *
 * \brief Memory with DMA functionality declaration.
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

#ifndef DMA_MEMORY_H_INCLUDED
#define DMA_MEMORY_H_INCLUDED

#include <hpl_dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup dma_memory
 *
 * \section dma_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

/**
 * \brief Memory with DMA descriptor
 *
 * The Memory with DMA descriptor forward declaration.
 */
struct dma_memory_descriptor;

/**
 * \brief memory with dma callback type
 */
typedef void (*dma_memory_cb_t)(void);

/**
* \brief Memory with DMA callback types
*/
enum dma_memory_callback_type { DMA_MEMORY_COMPLETE_CB, DMA_MEMORY_ERROR_CB };

/**
 * \brief Memory with DMA callbacks
 */
struct dma_memory_callbacks {
	dma_memory_cb_t complete;
	dma_memory_cb_t error;
};

/**
 * \brief Memory with DMA descriptor
 */
struct dma_memory_descriptor {
	struct _dma_resource *      resource;
	struct dma_memory_callbacks memory_cb;
};

/**
 * \brief Initialize Memory with DMA
 *
 * \return Initialization status.
 */
int32_t dma_memory_init(void);

/**
 * \brief Register Memory with DMA callback
 *
 * \param[in] type Callback type
 * \param[in] cb A callback function, passing NULL de-registers callback
 *
 * \return The status of callback assignment.
 * \retval ERR_INVALID_ARG Passed parameters were invalid
 * \retval ERR_NONE A callback is registered successfully
 */
int32_t dma_memory_register_callback(const enum dma_memory_callback_type type, dma_memory_cb_t cb);

/**
 * \brief dma memory copy
 *
 * \param[in] dst The pointer to destination address for transfer
 * \param[in] src The pointer to source address for transfer
 * \param[in] size The transfer size
 *
 * \return the status of operation`
 */
int32_t dma_memcpy(void *dst, void *src, uint32_t size);

/**
 * \brief dma memory set
 *
 * \param[in] dst The pointer to address to  fill
 * \param[in] ch The value to be filled
 * \param[in] size Number of bytes to set to the value
 *
 * \return the status of operation
 */
int32_t dma_memset(void *dst, int32_t ch, uint32_t size);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* DMA_MEMORY_H_INCLUDED */
