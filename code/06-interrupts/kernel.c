#include "include/os.h"

extern int dw8250_uart_init(void);
extern void dw8250_uart_isr(void);
extern void page_init(void);
extern void sched_init(void);
extern void schedule(void);
extern void os_main(void);
extern void trap_init(void);
extern void plic_init(void);

void start_kernel(void)
{
    dw8250_uart_init();
    dw8250_uart_puts("Hello, RVOS!\n");

    // while (1)
    // {

    //     dw8250_uart_isr();
    //     task_delay(1000);
    // }
    

    page_init();

    trap_init();

    plic_init();

    sched_init();

    os_main();

    schedule();

    dw8250_uart_puts("Would not go here!\n");
    // while(1){};

}
