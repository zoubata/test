/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

static void convert_cb_IO1_LIGHT_SENS(const struct adc_async_descriptor *const descr, const uint8_t channel)
{
}

/**
 * Example of using IO1_LIGHT_SENS to generate waveform.
 */
void IO1_LIGHT_SENS_example(void)
{
	adc_async_register_callback(&IO1_LIGHT_SENS, 0, ADC_ASYNC_CONVERT_CB, convert_cb_IO1_LIGHT_SENS);
	adc_async_enable_channel(&IO1_LIGHT_SENS, 0);
	adc_async_start_conversion(&IO1_LIGHT_SENS);
}

/**
 * Example of using IO1_LED_PWM.
 */
void IO1_LED_PWM_example(void)
{
	pwm_set_parameters(&IO1_LED_PWM, 10000, 5000);
	pwm_enable(&IO1_LED_PWM);
}
