#include "atmel_start.h"
#include <hal_gpio.h>
#include <hal_delay.h>

int main(void)
{
	atmel_start_init();

	while (true) {
		delay_ms(500);
		gpio_toggle_pin_level(LED0);
	}
}
