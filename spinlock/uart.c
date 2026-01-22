#include "uart.h"

#define UART0_BASE 0x10000000UL
#define UART_THR (*(volatile unsigned char *)(UART0_BASE + 0x00))
#define UART_LSR (*(volatile unsigned char *)(UART0_BASE + 0x05))
#define LSR_TX_IDLE 0x20

void uart_putc(char c)
{
    while ((UART_LSR & LSR_TX_IDLE) == 0);
    UART_THR = c;
}

void uart_puts(const char *s)
{
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}
