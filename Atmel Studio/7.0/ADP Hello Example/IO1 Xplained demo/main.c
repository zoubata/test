/**
 * \file
 *
 * \brief IO1 Xplained demo
 *
 * Copyright (C) 2014-2016 Atmel Corporation. All rights reserved.
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

#include "atmel_start.h"
#include "atmel_start_pins.h"
#include "io1_xplained_demo_config.h"
#include "temperature_sensor_main.h"

#include <hal_delay.h>
#include <stdio.h>
#include <string.h>

#define STR_SIZE 40

static struct io_descriptor *terminal_io;

void UART_EDBG_init()
{
	usart_sync_get_io_descriptor(&EDBG_COM, &terminal_io);
	usart_sync_enable(&EDBG_COM);
}

int main(void)
{
	uint16_t temp_result;
	uint8_t  light_sensor_result_buf[2];
	char     str[STR_SIZE];

	atmel_start_init();

	temperature_sensors_init();
	UART_EDBG_init();

	adc_sync_enable_channel(&IO1_LIGHT_SENS, CONF_ADC_CHANNEL);

	while (1) {

		delay_ms(1000);
		temp_result = (uint16_t)temperature_sensor_read(AT30TSE75X);

		adc_sync_read_channel(&IO1_LIGHT_SENS, CONF_ADC_CHANNEL, light_sensor_result_buf, 2);

		uint16_t light_sensor_result = *((uint16_t *)light_sensor_result_buf);

		snprintf(str, STR_SIZE, "Temperature: %d light sensor: %d\r\n", temp_result, light_sensor_result);

		io_write(terminal_io, (uint8_t *)str, strlen(str));
	}
}
