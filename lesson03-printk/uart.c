#include "uart.h"
#include "kernel.h"

#define UARTBASE             0x09000000

#define UART_DR              (UARTBASE + 0x00)
#define UART_FR              (UARTBASE + 0x18)
#define UART_FR_RXFE         (1 << 4)  /* recieve fifo empty */
#define UART_FR_TXFF         (1 << 5)  /* transmit fifo full */
#define UART_FR_RXFF         (1 << 6)  /* recieve fifo full */
#define UART_FR_TXFE         (1 << 7)  /* transmit fifo empty */
#define UART_IBRD            (UARTBASE + 0x24)
#define UART_FBRD            (UARTBASE + 0x28)
#define UART_LCRH            (UARTBASE + 0x2c)
#define LCRH_FEN             (1 << 4)
#define LCRH_WLEN_8BIT       (3 << 5)
#define UART_CR              (UARTBASE + 0x30)
#define UART_IMSC            (UARTBASE + 0x38)
#define UART_ICR             (UARTBASE + 0x44)

// 线控制寄存器位定义
#define UART_LCRH_WLEN_8BITS (3 << 5)  // 8位数据位
#define UART_LCRH_FEN        (1 << 4)  // 启用FIFO

// 控制寄存器位定义
#define UART_CR_UARTEN       (1 << 0)  // 启用UART
#define UART_CR_TXE          (1 << 8)  // 启用发送
#define UART_CR_RXE          (1 << 9)  // 启用接收


void uart_putc(char c)
{
    // 等待发送FIFO不满
    while (mmio_read(UART_FR) & UART_FR_TXFF);
    
    // 写入字符到数据寄存器
    mmio_write(UART_DR, c);
}

char uart_getc(void)
{
    // 等待接收FIFO不空
    while (mmio_read(UART_FR) & UART_FR_RXFE);
    
    // 从数据寄存器读取字符
    return mmio_read(UART_DR);
}

void uart_puts(const char *s)
{
    while (*s) {
        // 处理换行符，如果需要的话添加回车符
        if (*s == '\n') {
            uart_putc('\r');
        }
        uart_putc(*s++);
    }
}

void uart_init(void)
{
    // 禁用UART
    mmio_write(UART_CR, 0);
    
    // 设置波特率 (115200)
    mmio_write(UART_IBRD, 26);  // 整数部分
    mmio_write(UART_FBRD, 3);   // 小数部分
    
    // 设置数据格式: 8位数据, 1位停止位, 无奇偶校验, FIFO启用
    mmio_write(UART_LCRH, UART_LCRH_WLEN_8BITS | UART_LCRH_FEN);
    
    // 启用UART, 发送和接收
    mmio_write(UART_CR, UART_CR_UARTEN | UART_CR_TXE | UART_CR_RXE);
}