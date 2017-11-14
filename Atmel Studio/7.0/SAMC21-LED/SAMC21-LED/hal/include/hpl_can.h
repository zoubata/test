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

#ifndef HPL_CAN_H_INCLUDED
#define HPL_CAN_H_INCLUDED

#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup hpl_can CAN Common declaration
 *
 * \section can_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

/**
 * \brief CAN Message Format
 */
enum can_format {
	CAN_FMT_STDID, /*!< Standard Format, 11 bits identifier */
	CAN_FMT_EXTID  /*!< Extended Format, 29 bits identifier */
};

/**
 * \brief CAN Message Type
 */
enum can_type {
	CAN_TYPE_DATA,  /*!< A DATA FRAME carries data from a transmitter to the
                        receivers.*/
	CAN_TYPE_REMOTE /*!< A REMOTE FRAME is transmitted by a bus unit to request
                         the transmission of the DATA FRAME with the same
                         IDENTIFIER */
};

/**
 * \brief CAN Bus Mode
 */
enum can_mode {
	/** Normal operation Mode */
	CAN_MODE_NORMAL,
	/** In Bus Monitoring mode (see ISO11898-1, 10.12 Bus monitoring), the CAN
     * is able to receive valid data frames and valid remote frames, but
     * cannot start a transmission. In this mode, it sends only recessive bits
     * on the CAN bus. If the CAN is required to send a dominant bit (ACK bit,
     * overload flag, active error flag), the bit is rerouted internally so
     * that the CAN monitors this dominant bit, although the CAN bus may
     * remain in recessive state.
     * The Bus Monitoring mode can be used to analyze the traffic on a CAN bus
     * without affecting it by the transmission of dominant bits.
     */
	CAN_MODE_MONITORING
};

/**
 * \brief CAN Message
 */
struct can_message {
	uint32_t        id;   /* Message identifier */
	enum can_type   type; /* Message Type */
	uint8_t *       data; /* Pointer to Message Data */
	uint8_t         len;  /* Message Length */
	enum can_format fmt;  /* Identifier format, CAN_STD, CAN_EXT */
};

/**
 * \brief CAN Filter
 */
struct can_filter {
	uint32_t id;   /* Message identifier */
	uint32_t mask; /* The mask applied to the id */
};

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* HPL_CAN_H_INCLUDED */
