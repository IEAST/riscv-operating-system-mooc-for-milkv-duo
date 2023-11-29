    .equ STACK_SIZE, 16384
    .global _srart
    .text

_start:
    csrr t0, mhartid
    mv  tp, t0
    bnez t0,park

    la a0, _bss_start
    la a1, _bss_end
	bgeu	a0, a1, 2f
1:
	sw	zero, (a0)
	addi	a0, a0, 4
	bltu	a0, a1, 1b

2:
    slli t0, t0,10
    la sp, stacks + STACK_SIZE
    add sp, sp, t0
    j start_kernel

park:
    wfi
    j park

.align 16

stacks:
    .skip STACK_SIZE * 2
    .end
