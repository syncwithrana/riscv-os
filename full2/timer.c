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

    lo += 10000000;   /* slow tick */
    if (lo < 10000000)
        hi++;

    MTIMECMP_HI = hi;
    MTIMECMP_LO = lo;
}

void trap_handler_c(void)
{
    uart_putc('T');
    delays();
    timer_init();
    schedule();
}


static inline unsigned long long read_mtime(void)
{
    unsigned int hi1, lo, hi2;

    /* atomic 64-bit read on RV32 */
    do {
        hi1 = MTIME_HI;
        lo  = MTIME_LO;
        hi2 = MTIME_HI;
    } while (hi1 != hi2);

    return ((unsigned long long)hi1 << 32) | lo;
}

void delays(void)
{
    unsigned long long start = read_mtime();
    while (read_mtime() - start < 10000000ULL);
}
