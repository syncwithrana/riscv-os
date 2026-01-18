#include "uart.h"
#include "timer.h"
#include "context.h"
#include "tasks.h"

void main(void)
{
    uart_puts("SCHEDULER START\n");

    init_task(0, taskA);
    init_task(1, taskB);
    init_task(2, taskC);

    start_task();

    while (1);
}
