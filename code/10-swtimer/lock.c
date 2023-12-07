#include "include/os.h"


int spin_lock(struct spinlock *lk)
{
    w_mstatus(r_mstatus() & ~MSTATUS_MIE);
	return 0;
}

int spin_unlock(struct spinlock *lk){
    w_mstatus(r_mstatus() | MSTATUS_MIE);
	return 0;
}