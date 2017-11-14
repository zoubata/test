/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_adc_base.h>

/* The channel amount for ADC */
#define IO1_LIGHT_SENS_CH_AMOUNT 1

/* The buffer size for ADC */
#define IO1_LIGHT_SENS_BUFFER_SIZE 16

/* The maximal channel number of enabled channels */
#define IO1_LIGHT_SENS_CH_MAX 0

struct adc_async_descriptor         IO1_LIGHT_SENS;
struct adc_async_channel_descriptor IO1_LIGHT_SENS_ch[IO1_LIGHT_SENS_CH_AMOUNT];

static uint8_t IO1_LIGHT_SENS_buffer[IO1_LIGHT_SENS_BUFFER_SIZE];
static uint8_t IO1_LIGHT_SENS_map[IO1_LIGHT_SENS_CH_MAX + 1];

struct pwm_descriptor IO1_LED_PWM;

/**
 * \brief ADC initialization function
 *
 * Enables ADC peripheral, clocks and initializes ADC driver
 */
static void IO1_LIGHT_SENS_init(void)
{
	hri_mclk_set_APBCMASK_ADC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC0_GCLK_ID, CONF_GCLK_ADC0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	adc_async_init(&IO1_LIGHT_SENS,
	               ADC0,
	               IO1_LIGHT_SENS_map,
	               IO1_LIGHT_SENS_CH_MAX,
	               IO1_LIGHT_SENS_CH_AMOUNT,
	               &IO1_LIGHT_SENS_ch[0],
	               _adc_get_adc_async());
	adc_async_register_channel_buffer(&IO1_LIGHT_SENS, 0, IO1_LIGHT_SENS_buffer, IO1_LIGHT_SENS_BUFFER_SIZE);

	// Disable digital pin circuitry
	gpio_set_pin_direction(IO1_LIGHTSENSOR, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(IO1_LIGHTSENSOR, PINMUX_PB09B_ADC0_AIN3);
}

void IO1_LED_PWM_PORT_init(void)
{

	gpio_set_pin_function(IO1_LED, PINMUX_PB12F_TCC0_WO6);
}

void IO1_LED_PWM_CLOCK_init(void)
{
	hri_mclk_set_APBCMASK_TCC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TCC0_GCLK_ID, CONF_GCLK_TCC0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void IO1_LED_PWM_init(void)
{
	IO1_LED_PWM_CLOCK_init();
	IO1_LED_PWM_PORT_init();
	pwm_init(&IO1_LED_PWM, TCC0, _tcc_get_pwm());
}

void system_init(void)
{
	init_mcu();

	IO1_LIGHT_SENS_init();

	IO1_LED_PWM_init();
}
