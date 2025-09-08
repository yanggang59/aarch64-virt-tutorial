// printf.c
#include "printk.h"
#include "uart.h"

// 辅助函数：将数字转换为字符串并输出
static void print_number(unsigned long num, int base, int sign, int width) {
    char buffer[32] __attribute__((aligned(8)));
    char digits[] = "0123456789abcdef";
    int i = 0;
    
    // 处理符号
    if (sign && (long)num < 0) {
        uart_putc('-');
        num = -(long)num;
    }
    
    // 转换数字为字符串（反向）
    do {
        buffer[i++] = digits[num % base];
        num /= base;
    } while (num > 0);
    
    // 添加前导零以满足宽度要求
    while (i < width) {
        buffer[i++] = '0';
    }
    
    // 反向输出字符串（使其正向）
    while (--i >= 0) {
        uart_putc(buffer[i]);
    }
}

// 辅助函数：输出字符串
static void print_string(const char *str, int width) {
    int len = 0;
    const char *p = str;
    
    // 计算字符串长度
    while (*p++) len++;
    
    // 添加前导空格以满足宽度要求
    while (len < width) {
        uart_putc(' ');
        width--;
    }
    
    // 输出字符串
    while (*str) {
        uart_putc(*str++);
    }
}

// 主printf函数
void printk(const char *format, ...) {
    // 使用GCC内置函数处理可变参数
    __builtin_va_list args;
    __builtin_va_start(args, format);
    
    while (*format) {
        if (*format != '%') {
            uart_putc(*format++);
            continue;
        }
        
        // 处理格式说明符
        format++; // 跳过'%'
        
        // 解析宽度
        int width = 0;
        while (*format >= '0' && *format <= '9') {
            width = width * 10 + (*format - '0');
            format++;
        }
        
        // 处理格式字符
        switch (*format) {
            case 'c': {
                char c = __builtin_va_arg(args, int);
                uart_putc(c);
                break;
            }
            case 's': {
                char *str = __builtin_va_arg(args, char*);
                print_string(str, width);
                break;
            }
            case 'd': {
                int num = __builtin_va_arg(args, int);
                print_number(num, 10, 1, width);
                break;
            }
            case 'u': {
                unsigned int num = __builtin_va_arg(args, unsigned int);
                print_number(num, 10, 0, width);
                break;
            }
            case 'x': {
                unsigned int num = __builtin_va_arg(args, unsigned int);
                print_number(num, 16, 0, width);
                break;
            }
            case 'p': {
                void *ptr = __builtin_va_arg(args, void*);
                uart_puts("0x");
                print_number((unsigned long)ptr, 16, 0, sizeof(void*) * 2);
                break;
            }
            case '%': {
                uart_putc('%');
                break;
            }
            default: {
                uart_putc('%');
                uart_putc(*format);
                break;
            }
        }
        
        format++;
    }
    
    __builtin_va_end(args);
}
