#include "include/os.h"

void plic_init(void)
{
    int hart = r_tp();
    *(uint32_t*)PLIC_PRIORITY(UART0_IRQ) = 1;
    *(uint32_t*)PLIC_MENABLE(hart)= (1 << UART0_IRQ);
    *(uint32_t*)PLIC_MTHRESHOLD(hart) = 0;
    w_mie(r_mie() | MIE_MEIE);
    w_mstatus(r_mstatus() | MSTATUS_MIE);
}

int plic_claim(void)
{
    printf("in plic_claim \n");
    int hart = r_tp();
    int irq = *(uint32_t *)PLIC_MCLAIM(hart);
    return irq;
}

void plic_complete(int irq)
{
    printf("in plic_complete \n");
    int hart = r_tp();
    *(uint32_t *)PLIC_MCOMPLETE(hart) = irq;
}
