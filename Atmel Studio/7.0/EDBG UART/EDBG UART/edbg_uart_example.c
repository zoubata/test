#include "atmel_start.h"
#include "atmel_start_pins.h"
#include <string.h>

static uint8_t example_hello_world[12] = "Hello World!";

volatile static uint32_t data_arrived = 0;

static void tx_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
	gpio_toggle_pin_level(LED0);
}

static void rx_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* Receive completed */
	data_arrived = 1;
}

static void err_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* error handle */
	io_write(&EDBG_COM.io, example_hello_world, 12);
}

int main(void)
{
	uint8_t recv_char;

	atmel_start_init();

	usart_async_register_callback(&EDBG_COM, USART_ASYNC_TXC_CB, tx_cb_EDBG_COM);
	usart_async_register_callback(&EDBG_COM, USART_ASYNC_RXC_CB, rx_cb_EDBG_COM);
	usart_async_register_callback(&EDBG_COM, USART_ASYNC_ERROR_CB, err_cb_EDBG_COM);
	usart_async_enable(&EDBG_COM);

	io_write(&EDBG_COM.io, example_hello_world, 12);

	while (1) {
		if (data_arrived == 0) {
			continue;
		}

		while (io_read(&EDBG_COM.io, &recv_char, 1) == 1) {
			while (io_write(&EDBG_COM.io, &recv_char, 1) != 1) {
			}
		}
		data_arrived = 0;
	}
}
