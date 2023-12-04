#include "include/os.h"

#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

static uint64_t _tick = 0;

void timer_load(int interval)
{

    #ifdef QEMU
    uint64_t time = *(uint64_t*)(CLINT_MTIME + interval)
    #else
    uint64_t time = r_time()+interval;
    #endif
    
	*(uint32_t*)CLINT_MTIMECMPL0 = (time & 0xffffffff);
    *(uint32_t*)CLINT_MTIMECMPH0 = (time >> 32) & 0xffffffff;
}

void timer_init(){

    timer_load(TIMER_INTERVAL);
    w_mie(r_mie() | MIE_MTIE);
    w_mstatus(r_mstatus() | MSTATUS_MIE);
}

void timer_handler() 
{
	_tick++;
	printf("tick: %d\n", _tick);

	timer_load(TIMER_INTERVAL);
}