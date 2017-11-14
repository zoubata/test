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

#ifndef HPL_CAN_BASE_H_INCLUDED
#define HPL_CAN_BASE_H_INCLUDED

#include <utils_assert.h>
#include <hpl_can_config.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief CAN receive FIFO element.
 */
struct _can_rx_fifo_entry {
	__IO union {
		struct {
			uint32_t ID : 29; /*!< Identifier */
			uint32_t RTR : 1; /*!< Remote Transmission Request */
			uint32_t XTD : 1; /*!< Extended Identifier */
			uint32_t ESI : 1; /*!< Error State Indicator */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} R0;
	__IO union {
		struct {
			uint32_t RXTS : 16; /*!< Rx Timestamp */
			uint32_t DLC : 4;   /*!< Data Length Code */
			uint32_t BRS : 1;   /*!< Bit Rate Switch */
			uint32_t FDF : 1;   /*!< FD Format */
			uint32_t : 2;       /*!< Reserved */
			uint32_t FIDX : 7;  /*!< Filter Index */
			uint32_t ANMF : 1;  /*!< Accepted Non-matching Frame */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} R1;
	uint8_t data[];
};

/**
 * \brief CAN transmit FIFO element.
 */
struct _can_tx_fifo_entry {
	__IO union {
		struct {
			uint32_t ID : 29; /*!< Identifier */
			uint32_t RTR : 1; /*!< Remote Transmission Request */
			uint32_t XTD : 1; /*!< Extended Identifier */
			uint32_t ESI : 1; /*!< Error State Indicator */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} R0;
	__IO union {
		struct {
			uint32_t : 16;    /*!< Reserved */
			uint32_t DLC : 4; /*!< Data Length Code */
			uint32_t BRS : 1; /*!< Bit Rate Switch */
			uint32_t FDF : 1; /*!< FD Format */
			uint32_t : 1;     /*!< Reserved */
			uint32_t EFC : 1; /*!< Event FIFO Control */
			uint32_t MM : 8;  /*!< Message Marker */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} R1;
	uint8_t data[];
};

/**
 * \brief CAN transmit Event element.
 */
struct _can_tx_event_entry {
	__IO union {
		struct {
			uint32_t ID : 29; /*!< Identifier */
			uint32_t RTR : 1; /*!< Remote Transmission Request */
			uint32_t XTD : 1; /*!< Extended Identifier */
			uint32_t ESI : 1; /*!< Error State Indicator */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} R0;
	__IO union {
		struct {
			uint32_t TXTS : 16; /*!< Tx Timestamp */
			uint32_t DLC : 4;   /*!< Data Length Code */
			uint32_t BRS : 1;   /*!< Bit Rate Switch */
			uint32_t FDF : 1;   /*!< FD Format */
			uint32_t ET : 2;    /*!< Event Type */
			uint32_t MM : 8;    /*!< Message Marker */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} R1;
};

/**
 * \brief CAN standard message ID filter element structure.
 *
 *  Common element structure for standard message ID filter element.
 */
struct _can_standard_message_filter_element {
	__IO union {
		struct {
			uint32_t SFID2 : 11; /*!< Standard Filter ID 2 */
			uint32_t : 5;        /*!< Reserved */
			uint32_t SFID1 : 11; /*!< Standard Filter ID 1 */
			uint32_t SFEC : 3;   /*!< Standard Filter Configuration */
			uint32_t SFT : 2;    /*!< Standard Filter Type */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} S0;
};

#define _CAN_SFT_RANGE 0     /*!< Range filter from SFID1 to SFID2 */
#define _CAN_SFT_DUAL 1      /*!< Dual ID filter for SFID1 or SFID2 */
#define _CAN_SFT_CLASSIC 2   /*!< Classic filter: SFID1 = filter, SFID2 = mask */
#define _CAN_SFEC_DISABLE 0  /*!< Disable filter element */
#define _CAN_SFEC_STF0M 1    /*!< Store in Rx FIFO 0 if filter matches */
#define _CAN_SFEC_STF1M 2    /*!< Store in Rx FIFO 1 if filter matches */
#define _CAN_SFEC_REJECT 3   /*!< Reject ID if filter matches */
#define _CAN_SFEC_PRIORITY 4 /*!< Set priority if filter matches. */
#define _CAN_SFEC_PRIF0M 5   /*!< Set priority and store in FIFO 0 if filter matches */
#define _CAN_SFEC_PRIF1M 6   /*!< Set priority and store in FIFO 1 if filter matches. */
#define _CAN_SFEC_STRXBUF 7  /*!< Store into Rx Buffer or as debug message, configuration of SFT[1:0] ignored. */

#define _CAN_EFT_RANGE 0     /*!< Range filter from SFID1 to SFID2 */
#define _CAN_EFT_DUAL 1      /*!< Dual ID filter for SFID1 or SFID2 */
#define _CAN_EFT_CLASSIC 2   /*!< Classic filter: SFID1 = filter, SFID2 = mask */
#define _CAN_EFEC_DISABLE 0  /*!< Disable filter element */
#define _CAN_EFEC_STF0M 1    /*!< Store in Rx FIFO 0 if filter matches */
#define _CAN_EFEC_STF1M 2    /*!< Store in Rx FIFO 1 if filter matches */
#define _CAN_EFEC_REJECT 3   /*!< Reject ID if filter matches */
#define _CAN_EFEC_PRIORITY 4 /*!< Set priority if filter matches. */
#define _CAN_EFEC_PRIF0M 5   /*!< Set priority and store in FIFO 0 if filter matches */
#define _CAN_EFEC_PRIF1M 6   /*!< Set priority and store in FIFO 1 if filter matches. */
#define _CAN_EFEC_STRXBUF 7  /*!< Store into Rx Buffer or as debug message, configuration of SFT[1:0] ignored. */
                             /**
                              * \brief CAN extended message ID filter element structure.
                              *
                              *  Common element structure for extended message ID filter element.
                              */
struct _can_extended_message_filter_element {
	__IO union {
		struct {
			uint32_t EFID1 : 29; /*!< bit: Extended Filter ID 1 */
			uint32_t EFEC : 3;   /*!< bit: Extended Filter Configuration */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} F0;
	__IO union {
		struct {
			uint32_t EFID2 : 29; /*!< bit: Extended Filter ID 2 */
			uint32_t : 1;        /*!< bit: Reserved */
			uint32_t EFT : 2;    /*!< bit: Extended Filter Type */
		} bit;
		uint32_t val; /*!< Type used for register access */
	} F1;
};

struct _can_context {
	uint8_t *                   rx_fifo;  /*!< receive message fifo */
	uint8_t *                   tx_fifo;  /*!< transfer message fifo */
	struct _can_tx_event_entry *tx_event; /*!< transfer event fifo */
	/* Standard filter List */
	struct _can_standard_message_filter_element *rx_std_filter;
	/* Extended filter List */
	struct _can_extended_message_filter_element *rx_ext_filter;
};

#ifdef __cplusplus
}
#endif

#endif /* HPL_CAN_BASE_H_INCLUDED */
