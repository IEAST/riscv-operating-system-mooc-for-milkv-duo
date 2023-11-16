#include "include/os.h"

extern void dw8250_uart_init(void);
extern void page_init(void);
extern void sched_init(void);
extern void schedule(void);
extern void os_main(void);
extern void trap_init(void);

void start_kernel(void)
{
    dw8250_uart_init();
    dw8250_uart_puts("Hello, RVOS!\n");

    page_init();

    trap_init();

    sched_init();

    os_main();

    schedule();

    dw8250_uart_puts("Would not go here!\n");
    // while(1){};

}