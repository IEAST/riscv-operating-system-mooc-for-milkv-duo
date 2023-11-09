#ifndef __OS_H__
#define __OS_H__

#include "drv_types.h"

#include <stddef.h>
#include <stdarg.h>


/* uart */
extern int dw8250_uart_putc(char c);
extern int dw8250_uart_puts(char *s);

/* printf */
extern int  printf(const char* s, ...);
extern void panic(char *s);

/* memory management */
extern void *page_alloc(int npages);
extern void page_free(void *p);

#endif /* __OS_H__ */