#include "uart.h"


static void myputchar(char c)
{
    uart_putc(c);
}

static void myprint(const char *s)
{
    while(*s != '\0')
    {
        myputchar(*s);
        s++;
    }
}

void kernel_main(void)
{
     myprint("Test UART \r\n");
     myprint("Hello world!\n");
     while (1) {
	}
}