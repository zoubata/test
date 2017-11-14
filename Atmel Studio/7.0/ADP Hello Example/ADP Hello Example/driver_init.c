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

struct spi_m_sync_descriptor EDBG_SPI;

void EDBG_SPI_PORT_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(EDBG_SPI_MISO, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(EDBG_SPI_MISO,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(EDBG_SPI_MISO, PINMUX_PB02D_SERCOM5_PAD0);

	// Set pin direction to output
	gpio_set_pin_direction(EDBG_SPI_MOSI, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EDBG_SPI_MOSI,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(EDBG_SPI_MOSI, PINMUX_PB00D_SERCOM5_PAD2);

	// Set pin direction to output
	gpio_set_pin_direction(EDBG_SPI_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EDBG_SPI_SCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(EDBG_SPI_SCK, PINMUX_PB01D_SERCOM5_PAD3);
}

void EDBG_SPI_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM5_GCLK_ID_CORE, CONF_GCLK_SERCOM5_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM5_GCLK_ID_SLOW, CONF_GCLK_SERCOM5_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_SERCOM5_bit(MCLK);
}

void EDBG_SPI_init(void)
{
	EDBG_SPI_CLOCK_init();
	spi_m_sync_init(&EDBG_SPI, SERCOM5);
	EDBG_SPI_PORT_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PB23

	// Set pin direction to output
	gpio_set_pin_direction(EDBG_SPI_SS_PIN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EDBG_SPI_SS_PIN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(EDBG_SPI_SS_PIN, GPIO_PIN_FUNCTION_OFF);

	EDBG_SPI_init();
}
