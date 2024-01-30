#include "include/os.h"

void plic_init(void)
{
    int hart = r_tp();
    *(uint32_t*)PLIC_PRIORITY(UART0_IRQ) = 1;
    *(uint32_t*)PLIC_MENABLE(UART0_IRQ) = (1 << (UART0_IRQ % 32));
    *(uint32_t*)PLIC_MTHRESHOLD = 0;
    w_mie(r_mie() | MIE_MEIE);
    
}

int plic_claim(void)
{
    int hart = r_tp();
    int irq = *(uint32_t *)PLIC_MCLAIM;
    return irq;
}

void plic_complete(int irq)
{
    int hart = r_tp();
    *(uint32_t *)PLIC_MCOMPLETE = irq;
}
