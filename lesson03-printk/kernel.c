#include "uart.h"
#include "printk.h"

void kernel_main(void)
{
    uart_init();
    uart_puts("Hello World!\n");
    printk("This is a test for printk , 0x%x\n", 5678);
    while (1)
    {
        
	}
}