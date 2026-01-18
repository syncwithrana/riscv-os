#include "uart.h"
#include "task.h"

#define MAX_TASKS 3

/* CLINT (RV32 safe) */
#define MTIMECMP_LO (*(volatile unsigned int *)0x02004000)
#define MTIMECMP_HI (*(volatile unsigned int *)0x02004004)
#define MTIME_LO    (*(volatile unsigned int *)0x0200BFF8)
#define MTIME_HI    (*(volatile unsigned int *)0x0200BFFC)

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

struct task tasks[MAX_TASKS];
int current = 0;

/* -------- Tasks -------- */

void taskA(void)
{
    while (1) {
        delays();
        uart_putc('A');
    }
}

void taskB(void)
{
    while (1) {
        delays();
        uart_putc('B');
    }
}

void taskC(void)
{
    while (1) {
        delays();
        uart_putc('C');
    }
}

/* -------- Timer -------- */

void timer_init(void)
{
    unsigned int lo, hi;

    MTIMECMP_HI = 0xffffffff;
    MTIMECMP_LO = 0xffffffff;

    hi = MTIME_HI;
    lo = MTIME_LO;

    lo += 1000000;
    if (lo < 1000000)
        hi++;

    MTIMECMP_HI = hi;
    MTIMECMP_LO = lo;
}

/* -------- Trap handler -------- */

void trap_handler_c(struct trapframe *tf)
{
    tasks[current].tf = *tf;

    current++;
    if (current >= MAX_TASKS)
        current = 0;

    *tf = tasks[current].tf;

    timer_init();
}

/* -------- Init -------- */

void init_task(int id, void (*fn)(void))
{
    struct trapframe *tf = &tasks[id].tf;

    tf->sp   = (unsigned int)(tasks[id].stack + STACK_SIZE);
    tf->mepc = (unsigned int)fn;
    tf->ra   = 0;
}

void main(void)
{
    uart_puts("\nSTEP 5 START\n");

    init_task(0, taskA);
    init_task(1, taskB);
    init_task(2, taskC);

    timer_init();

asm volatile(
    "csrw mscratch, %0\n"
    "csrw mepc, %1\n"
    "mv sp, %0\n"
    "mret\n"
    :
    : "r"(tasks[0].tf.sp),
      "r"(tasks[0].tf.mepc)
);
}
