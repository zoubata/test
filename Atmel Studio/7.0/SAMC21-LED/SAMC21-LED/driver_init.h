/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_ac_sync.h>

#include <hal_adc_sync.h>

#include <hal_crc_sync.h>
#include <hal_ext_irq.h>

#include <hal_flash.h>

#include <hal_pac.h>

#include <hal_calendar.h>

#include <hal_i2c_m_sync.h>
#include <hal_spi_m_sync.h>
#include <hal_spi_m_sync.h>

#include <hal_i2c_m_sync.h>

#include <hal_delay.h>
#include <hal_pwm.h>
#include <hpl_tc_base.h>
#include <hal_pwm.h>
#include <hpl_tc_base.h>

#include <hal_wdt.h>
#include <hal_can_async.h>

#include <hal_dac_sync.h>

#include <hal_evsys.h>

#include <hal_freqmeter_sync.h>

extern struct ac_sync_descriptor AC_0;

extern struct adc_sync_descriptor ADC_0;
extern struct crc_sync_descriptor CRC_0;

extern struct flash_descriptor FLASH_0;

extern struct calendar_descriptor CALENDAR_0;

extern struct i2c_m_sync_desc       I2C_0;
extern struct spi_m_sync_descriptor SPI_0;
extern struct spi_m_sync_descriptor SPI_1;

extern struct i2c_m_sync_desc I2C_1;

extern struct pwm_descriptor PWM_0;

extern struct pwm_descriptor PWM_1;

extern struct wdt_descriptor       WDT_0;
extern struct can_async_descriptor CAN_0;

extern struct dac_sync_descriptor DAC_0;

extern struct freqmeter_sync_descriptor FREQUENCY_METER_0;

void AC_0_PORT_init(void);
void AC_0_CLOCK_init(void);
void AC_0_init(void);

void ADC_0_PORT_init(void);
void ADC_0_CLOCK_init(void);
void ADC_0_init(void);

void FLASH_0_init(void);
void FLASH_0_CLOCK_init(void);

void CALENDAR_0_CLOCK_init(void);
void CALENDAR_0_init(void);

void I2C_0_CLOCK_init(void);
void I2C_0_init(void);
void I2C_0_PORT_init(void);

void SPI_0_PORT_init(void);
void SPI_0_CLOCK_init(void);
void SPI_0_init(void);

void SPI_1_PORT_init(void);
void SPI_1_CLOCK_init(void);
void SPI_1_init(void);

void I2C_1_CLOCK_init(void);
void I2C_1_init(void);
void I2C_1_PORT_init(void);

void delay_driver_init(void);

void PWM_0_PORT_init(void);
void PWM_0_CLOCK_init(void);
void PWM_0_init(void);

void PWM_1_PORT_init(void);
void PWM_1_CLOCK_init(void);
void PWM_1_init(void);

void WDT_0_CLOCK_init(void);
void WDT_0_init(void);

void DAC_0_PORT_init(void);
void DAC_0_CLOCK_init(void);
void DAC_0_init(void);

void FREQUENCY_METER_0_CLOCK_init(void);
void FREQUENCY_METER_0_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
