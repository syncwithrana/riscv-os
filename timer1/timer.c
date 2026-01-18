#include "uart.h"
#include "timer.h"
#include "tasks.h"

void timer_init(void)
{
    unsigned int lo, hi;

    MTIMECMP_HI = 0xffffffff;
    MTIMECMP_LO = 0xffffffff;

    hi = MTIME_HI;
    lo = MTIME_LO;

    lo += 50000000;   /* slow tick */
    if (lo < 50000000)
        hi++;

    MTIMECMP_HI = hi;
    MTIMECMP_LO = lo;
}

void timer_handler(void)
{
    uart_putc('T');
    //schedule();
    timer_init();
}