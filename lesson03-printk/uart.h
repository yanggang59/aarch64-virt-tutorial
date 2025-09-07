#ifndef __UART_H__
#define __UART_H__

void uart_putc(char c);
void uart_puts(const char *s);
void __putchar(char c);
char uart_getc(void);
void uart_init(void);

#endif