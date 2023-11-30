#include "include/os.h"

#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

static uint64_t _tick = 0;

void timer_load(int interval)
{
	/* each CPU has a separate source of timer interrupts. */
	
	*(uint64_t*)CLINT_MTIMECMP= (*(uint64_t*)CLINT_MTIME + interval);
}

void timer_init(){

    printf("time init\n");

    timer_load(TIMER_INTERVAL);
    printf("time init 2\n");
    w_mie(r_mie() | MIE_MTIE);
    printf("time init 3\n");
    w_mstatus(r_mstatus() | MSTATUS_MIE);
    printf("time init 4\n");
}

void timer_handler() 
{
	_tick++;
	printf("tick: %d\n", _tick);

	timer_load(TIMER_INTERVAL);
}