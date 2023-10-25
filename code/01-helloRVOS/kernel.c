#include "include/drv_uart.h"

void start_kernel(void)
{
    dw8250_uart_init();
    dw8250_uart_putc('H');
    dw8250_uart_putc('e');
    dw8250_uart_putc('l');
    dw8250_uart_putc('l');
    dw8250_uart_putc('o');
    dw8250_uart_putc('\n');
    dw8250_uart_puts("Hello, RVOS!\n");
}