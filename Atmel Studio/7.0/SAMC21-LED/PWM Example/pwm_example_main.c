#include "atmel_start.h"
#include "atmel_start_pins.h"
#include "pwm_example_config.h"
#include <hal_delay.h>

/* the pwm period for application is 10ms */
#define PWM_PERIOD 10000

static uint32_t pwm_duty;
static uint8_t  adc_values[2];

/**
 * \brief ADC callback about conversion completion
 *
 * \param[in] descr The pointer to corresponding ADC descriptor
 */
static void adc_cb(const struct adc_async_descriptor *const descr, const uint8_t channel)
{
	adc_async_read_channel(&IO1_LIGHT_SENS, channel, adc_values, CONF_ADC_BYTES);
	if (CONF_ADC_BYTES == 1) {
		pwm_duty = ((uint32_t)PWM_PERIOD * adc_values[0]) / 0xFF;
	} else {
		pwm_duty = ((uint32_t)PWM_PERIOD * (adc_values[0] + 256 * adc_values[1])) / 0xFFFF;
	}
	pwm_set_parameters(&IO1_LED_PWM, PWM_PERIOD, pwm_duty);
}

int main(void)
{
	atmel_start_init();

	adc_async_register_callback(&IO1_LIGHT_SENS, CONF_ADC_CHANNEL, ADC_ASYNC_CONVERT_CB, adc_cb);
	adc_async_enable_channel(&IO1_LIGHT_SENS, CONF_ADC_CHANNEL);
	pwm_enable(&IO1_LED_PWM);

	while (1) {
		adc_async_start_conversion(&IO1_LIGHT_SENS);
		delay_ms(100);
	}
}
