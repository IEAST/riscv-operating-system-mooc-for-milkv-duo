#include "include/os.h"

extern void trap_vector(void);

void trap_init(){
    w_mtvec((reg_t)trap_vector);
}

reg_t trap_handler(reg_t epc, reg_t cause){
    reg_t return_pc = epc;
    reg_t cause_code = cause & 0xfff;
    if (cause & 0x80000000) {
		/* Asynchronous trap - interrupt */
		switch (cause_code) {
		case 3:
			printf("software interruption!\n");
			break;
		case 7:
			printf("timer interruption!\n");
			break;
		case 11:
			printf("external interruption!\n");
			break;
		default:
			printf("unknown async exception!\n");
			break;
		}
	} else {
		/* Synchronous trap - exception */
		printf("Sync exceptions!, code = %d\n", cause_code);
		// panic("OOPS! What can I do!");
		return_pc += 2;
	}
	return return_pc;
}

void trap_test(){
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

	dw8250_uart_puts("Yeah! I'm return back from trap!\n");

}