CROSS_COMPILE =  riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -mcmodel=medany -march=rv64imafd -g -Wall -Iinclude

#GDB = riscv64-elf-gdb
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
LD = ${CROSS_COMPILE}ld

QEMU = y
ifeq (${QEMU}, y)
CFLAGS += -D QEMU
endif

#QEMU = ~/Tmp/plct-qemu/build/qemu-system-riscv64 
QFLAGS = -M milkv_duo -nographic -smp 1 -bios none
