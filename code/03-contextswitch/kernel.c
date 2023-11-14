#include "include/os.h"

extern void dw8250_uart_init(void);
extern void page_init(void);
extern void sched_init(void);
extern void schedule(void);

void start_kernel(void)
{
    dw8250_uart_init();
    dw8250_uart_puts("Hello, RVOS!\n");

    page_init();

    sched_init();

    schedule();

    dw8250_uart_puts("Would not go here!\n");
    // while(1){};

}