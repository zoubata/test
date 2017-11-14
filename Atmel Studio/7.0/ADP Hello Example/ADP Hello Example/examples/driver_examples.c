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

/**
 * Example of using EDBG_SPI to write "Hello World" using the IO abstraction.
 */
static uint8_t example_EDBG_SPI[12] = "Hello World!";

void EDBG_SPI_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&EDBG_SPI, &io);

	spi_m_sync_enable(&EDBG_SPI);
	io_write(io, example_EDBG_SPI, 12);
}
