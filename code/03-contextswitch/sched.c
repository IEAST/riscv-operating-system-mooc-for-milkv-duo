#include "include/os.h"

/* defined in entry.S */
extern void switch_to(struct context *next);

#define STACK_SIZE 16384
/*
 * In the standard RISC-V calling convention, the stack pointer sp
 * is always 16-byte aligned.
 */
uint8_t __attribute__((aligned(16))) task_stack[STACK_SIZE];
struct context ctx_task;

static void w_mscratch(reg_t x)
{
	printf("in w_mscratch\n");
	asm volatile("csrw mscratch, %0" : : "r" (x));
	
}

void user_task0(void);
void sched_init()
{
	printf("in sched_init\n");
	w_mscratch(0);
	printf("in sched_init 2\n");
	ctx_task.sp = (reg_t) &task_stack[STACK_SIZE];
	ctx_task.ra = (reg_t) user_task0;
}

void schedule()
{
	printf("in schedule\n");
	struct context *next = &ctx_task;
	printf("in schedule 2\n");
	printf(next);
	switch_to(next);
}

/*
 * a very rough implementaion, just to consume the cpu
 */
void task_delay(volatile int count)
{
	count *= 50000;
	while (count--);
}


void user_task0(void)
{
	printf("Task 0: Created!\n");
	while (1) {
		printf("Task 0: Running...\n");
		task_delay(1000);
	}
}

