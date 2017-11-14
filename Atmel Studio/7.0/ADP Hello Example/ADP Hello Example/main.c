#include "atmel_start.h"
#include "atmel_start_pins.h"
#include "adp_main.h"

int main(void)
{
	atmel_start_init();

	spi_m_sync_enable(&EDBG_SPI);
	adp_app_init();
	adp_interface_init_spi(&EDBG_SPI.io, EDBG_SPI_SS_PIN);
	ADP_example();
}
