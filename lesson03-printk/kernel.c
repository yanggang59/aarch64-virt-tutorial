#include "uart.h"


static void __putchar(char c)
{
    uart_putc(c);
}

static void print(const char *s)
{
    while(*s != '\0')
    {
        __putchar(*s);
        s++;
    }
}

void kernel_main(void)
{
     uart_puts("Test uart \r\n");
     print("Hello world!\n");
     while (1) {
	}
}