#include "include/os.h"

extern void trap_vector(void);
extern void dw8250_uart_isr(void);

void trap_init(){
	printf("in trap_init\n");
    w_mtvec((reg_t)trap_vector);
}

void external_interrupt_handler()
{
	int irq = plic_claim();


	if (irq == UART0_IRQ){
      		dw8250_uart_isr();
	} else if (irq) {
		printf("unexpected interrupt irq = %d\n", irq);
	}
	
	if (irq) {
		plic_complete(irq);
	}
}

reg_t trap_handler(reg_t epc, reg_t cause){

    reg_t return_pc = epc;
    reg_t cause_code = cause & 0xfff;

    if (cause & 0x8000000000000000) {
		/* Asynchronous trap - interrupt */
		switch (cause_code) {
		case 3:
			printf("software interruption!\n");
			break;
		case 7:
			printf("timer interruption!\n");
			timer_handler();
			break;
		case 11:
			printf("external interruption!\n");
			external_interrupt_handler();
			break;
		default:
			printf("unknown async exception!\n");
			break;
		}
	} else {
		/* Synchronous trap - exception */
		printf("cause======== %dx \n",cause);
		printf("Sync exceptions!, code = %d\n", cause_code);
		panic("OOPS! What can I do!");
		// return_pc += 4;
	}
	return return_pc;
}

void trap_test()
{
	/*
	 * Synchronous exception code = 7
	 * Store/AMO access fault
	 */
	*(int *)0x00000000 = 100;

	/*
	 * Synchronous exception code = 5
	 * Load access fault
	 */
	//int a = *(int *)0x00000000;

	printf("Yeah! I'm return back from trap!\n");
}