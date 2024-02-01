#include "include/os.h"

extern void schedule(void);

#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

#define MAX_TIMER 10
static struct timer timer_list[MAX_TIMER];

static uint64_t _tick = 0;

void timer_load(int interval)
{
    int id = r_mhartid();
    #ifdef QEMU
    *(uint64_t*)CLINT_MTIMECMP(id) = *(uint64_t*)CLINT_MTIME + interval;
    #else
    uint64_t time = r_time()+interval;
    *(uint32_t*)CLINT_MTIMECMPL(id) = (time & 0xffffffff);
    *(uint32_t*)CLINT_MTIMECMPH(id) = (time >> 32) & 0xffffffff;
    #endif
}

void timer_init()
{
    struct timer *t = &(timer_list[0]);
    for (int i = 0; i < MAX_TIMER; i++)
    {
        t->func = NULL;
        t->arg = NULL;
        t++;
    }

    timer_load(TIMER_INTERVAL);
    w_mie(r_mie() | MIE_MTIE);
}

struct timer *timer_create(void (*handler)(void *arg), void *arg, uint64_t timeout)
{
    /* TBD: params should be checked more, but now we just simplify this */
    if (NULL == handler || 0 == timeout)
    {
        return NULL;
    }

    /* use lock to protect the shared timer_list between multiple tasks */
    spin_lock();

    struct timer *t = &(timer_list[0]);

    for (int i = 0; i < MAX_TIMER; i++)
    {
        if (NULL == t->func)
        {
            break;
        }
        t++;
    }
    if (NULL != t->func)
    {
        spin_unlock();
        return NULL;
    }

    t->func = handler;
    t->arg = arg;
    t->timeout_tick = _tick + timeout;

    spin_unlock();

    return t;
}

void timer_delete(struct timer *timer)
{
    spin_lock();

    struct timer *t = &(timer_list[0]);
    for (int i = 0; i < MAX_TIMER; i++)
    {
        if (t == timer)
        {
            t->func = NULL;
            t->arg = NULL;
            break;
        }
        t++;
    }
    spin_unlock();
}
/* this routine should be called in interrupt context (interrupt is disabled) */
static inline void timer_check(){
    struct timer *t =&(timer_list[0]);
    for (int i=0;i< MAX_TIMER; i++){
        if(NULL != t->func){
            if(_tick >= t-> timeout_tick){
                t->func(t->arg);

                /* once time, just delete it after timeout */
                t->func = NULL;
                t->arg = NULL;

                break;
            }
        }
        t++;
    }
    
}

void timer_handler()
{
    _tick++;
    printf("tick: %d\n", _tick);

    timer_check();
    
    timer_load(TIMER_INTERVAL);

    schedule();
}
