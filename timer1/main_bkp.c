#include "uart.h"
#include "timer.h"

void main(void)
{
    uart_puts("TIMER TEST START\n");
    timer_init();

    while (1);
}
