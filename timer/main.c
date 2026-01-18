#include "context.h"
#include "uart.h"

/* CLINT (RV32 safe) */
#define MTIMECMP_LO (*(volatile unsigned int *)0x02004000)
#define MTIMECMP_HI (*(volatile unsigned int *)0x02004004)
#define MTIME_LO    (*(volatile unsigned int *)0x0200BFF8)
#define MTIME_HI    (*(volatile unsigned int *)0x0200BFFC)

#define MAX_TASKS 3
#define STACK_SIZE 1024

extern void context_switch(struct context*, struct context*);

unsigned char stacks[MAX_TASKS][STACK_SIZE];
struct context tasks[MAX_TASKS];

int current = 0;

/* -------- Tasks -------- */

void taskA(void) {
    uart_puts("A\n");
    while (1);
}

void taskB(void) {
    uart_puts("B\n");
    while (1);
}

void taskC(void) {
    uart_puts("C\n");
    while (1);
}

/* -------- Scheduler -------- */

void init_context(int i, void (*fn)(void)) {
    tasks[i].ra = (unsigned int)fn;
    tasks[i].sp = (unsigned int)(stacks[i] + STACK_SIZE);
}

void yield(void) {
    int prev = current;
    current++;
    if (current >= MAX_TASKS) current = 0;
    context_switch(&tasks[prev], &tasks[current]);
}

/* -------- Timer -------- */

void timer_init(void)
{
    unsigned int lo, hi;

    MTIMECMP_HI = 0xffffffff;
    MTIMECMP_LO = 0xffffffff;

    hi = MTIME_HI;
    lo = MTIME_LO;

    lo += 50000000;
    if (lo < 50000000) hi++;

    MTIMECMP_HI = hi;
    MTIMECMP_LO = lo;
}

void timer_handler(void)
{
    timer_init();
    yield();
}

/* -------- Entry -------- */

void main(void)
{
    uart_init();
    uart_puts("BOOT\n");

    init_context(0, taskA);
    init_context(1, taskB);
    init_context(2, taskC);

    timer_init();
    context_switch(&(struct context){0}, &tasks[0]);

    while (1);
}
