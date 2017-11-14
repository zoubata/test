#include "atmel_start.h"
#include <hal_gpio.h>
#include <hal_delay.h>

int main(void)
{
	atmel_start_init();

	gpio_set_pin_pull_mode(SW0, GPIO_PULL_UP);

	while (true) {
		do {
			delay_ms(100);
		} while (gpio_get_pin_level(SW0));

		gpio_toggle_pin_level(LED0);

		do {
			delay_ms(100);
		} while (!gpio_get_pin_level(SW0));
	}
	
}
