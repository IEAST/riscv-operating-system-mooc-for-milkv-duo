CROSS_COMPILE = riscv64-elf-
CFLAGS = -nostdlib -fno-builtin -mcmodel=medany -g -Wall -Iinclude

GDB = riscv64-elf-gdb
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
LD = ${CROSS_COMPILE}ld
