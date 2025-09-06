#include "uart.h"
#include "kernel.h"

#define UARTBASE   0x09000000

#define UART_DR (UARTBASE + 0x00)
#define UART_FR (UARTBASE + 0x18)
#define FR_RXFE (1 << 4)  /* recieve fifo empty */
#define FR_TXFF (1 << 5)  /* transmit fifo full */
#define FR_RXFF (1 << 6)  /* recieve fifo full */
#define FR_TXFE (1 << 7)  /* transmit fifo empty */
#define RXFE    (REG(UART_FR) & FR_RXFE)
#define TXFF    (REG(UART_FR) & FR_TXFF)
#define RXFF    (REG(UART_FR) & FR_RXFF)
#define TXFE    (REG(UART_FR) & FR_TXFE)
#define UART_IBRD (UARTBASE + 0x24)
#define UART_FBRD (UARTBASE + 0x28)
#define UART_LCRH (UARTBASE + 0x2c)
#define LCRH_FEN  (1 << 4)
#define LCRH_WLEN_8BIT  (3 << 5)
#define UART_CR (UARTBASE + 0x30)
#define UART_IMSC (UARTBASE + 0x38)
#define UART_ICR  (UARTBASE + 0x44)


int uart_getc(void);

void uart_putc(char c) {
  while(REG(UART_FR) & FR_TXFF)
    ;
  REG(UART_DR) = c;
}

int uart_getc() {
  if(REG(UART_FR) & FR_RXFE)
    return -1;

  return REG(UART_DR);
}

void uart_puts(char *s) {
  char c;
  while((c = *s)) {
    uart_putc(c);
    s++;
  }
}