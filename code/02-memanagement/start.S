#define UART0_THR 0x04140000
#define UART0_LSR 0x04140014

    .equ STACK_SIZE, 16384
    .global _srart
    .text

_srart:
    csrr t0, mhartid
    mv  tp, t0
    bnez t0,park
    slli t0, t0,10
    la sp, stacks + STACK_SIZE
    add sp, sp, t0
    j start_kernel

park:
    wfi
    j park

.align 4

stacks:
    .skip STACK_SIZE
    .end
