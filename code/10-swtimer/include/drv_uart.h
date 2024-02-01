#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#define UART_REG_SHIFT 0x2 /* Register Shift*/
#define UART_INPUT_CLK 25000000

#define UART0_BASE 0x04140000 /*UART0 Address */
#define UART1_BASE 0x04150000
#define UART2_BASE 0x04160000
#define UART3_BASE 0x04170000
#define UART4_BASE 0x041C0000

#define UART_IRQ_BASE (44)
#define UART0_IRQ (UART_IRQ_BASE + 0)
#define UART1_IRQ (UART_IRQ_BASE + 1)
#define UART2_IRQ (UART_IRQ_BASE + 2)
#define UART3_IRQ (UART_IRQ_BASE + 3)
#define UART4_IRQ (UART_IRQ_BASE + 4)

extern int dw8250_uart_init();
extern int dw8250_uart_putc(char c);
extern int dw8250_uart_puts(char *s);

/*
 * This machine puts platform-level interrupt controller (PLIC) here.
 * Here only list PLIC registers in Machine mode.
 * see https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 * #define VIRT_PLIC_HART_CONFIG "MS"
 * #define VIRT_PLIC_NUM_SOURCES 127
 * #define VIRT_PLIC_NUM_PRIORITIES 7
 * #define VIRT_PLIC_PRIORITY_BASE 0x04
 * #define VIRT_PLIC_PENDING_BASE 0x1000
 * #define VIRT_PLIC_ENABLE_BASE 0x2000
 * #define VIRT_PLIC_ENABLE_STRIDE 0x80
 * #define VIRT_PLIC_CONTEXT_BASE 0x200000
 * #define VIRT_PLIC_CONTEXT_STRIDE 0x1000
 * #define VIRT_PLIC_SIZE(__num_context) \
 *     (VIRT_PLIC_CONTEXT_BASE + (__num_context) * VIRT_PLIC_CONTEXT_STRIDE)
 */
/*
因为 Duo 手册上没有 PLIC 相关的内容，但是 Duo 参考了玄铁 C9006 进行设计，
寄存器设计参考了C9006 相关手册。
*/
#define PLIC_BASE 0x70000000L
#define PLIC_PRIORITY(id) (PLIC_BASE + (id) * 4)
#define PLIC_PENDING(id) (PLIC_BASE + 0x1000 + ((id) / 32) * 4)
#define PLIC_MENABLE(id) (PLIC_BASE + 0x2000 + ((id) / 32) * 4)
#define PLIC_MTHRESHOLD (PLIC_BASE + 0x200000 )
#define PLIC_MCLAIM (PLIC_BASE + 0x200004)
#define PLIC_MCOMPLETE (PLIC_BASE + 0x200004)

// 具体参照芯片手册定时器的章节,在 cv1800b 中，无法通过读取寄存器直接获取 mtime ,需要通过 rtime 来获取。

// #ifdef QEMU

#define CLINT_BASE 0x74000000L
#define CLINT_MSIP(hartid) (CLINT_BASE + 4 * (hartid))
#define CLINT_MTIMECMP(hartid) (CLINT_BASE + 0x4000 + 8 * (hartid))
#define CLINT_MTIME (CLINT_BASE + 0xBFF8) // cycles since boot.
#define CLINT_TIMEBASE_FREQ 10000000

#else
#define CLINT_BASE 0x74000000L
#define CLINT_MSIP(hartid) (CLINT_BASE + 4 * (hartid))
#define CLINT_MTIMECMPL(hartid) (CLINT_BASE + 0x4000 + 8 * (hartid))
#define CLINT_MTIMECMPH(hartid) (CLINT_BASE + 0x4004 + 8 * (hartid))
#define CLINT_TIMEBASE_FREQ 25000000
#endif

#endif /* __DRV_USART_H__ */