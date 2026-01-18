#include "uart.h"
#include "context.h"
#include "tasks.h"
#include "timer.h"

/* ---------- Scheduler ---------- */
#define NTASKS 3
#define STACK_SIZE 1024

unsigned char stacks[NTASKS][STACK_SIZE];
struct context tasks[NTASKS];

int current = 0;

/* ---------- Tasks ---------- */

void taskA(void) {
    uart_puts("A\n");
    timer_init();
    while (1);
}

void taskB(void) {
    uart_puts("B\n");
    timer_init();
    while (1);
}

void taskC(void) {
    uart_puts("C\n");
    timer_init();
    while (1);
}

void init_task(int i, void (*fn)(void))
{
    tasks[i].ra = (unsigned int)fn;
    tasks[i].sp = (unsigned int)(stacks[i] + STACK_SIZE);
}

void task_switch(void)
{
    current = 0;
    context_switch(&(struct context){0}, &tasks[0]);
}

void schedule(void)
{
    uart_puts("\nSCHEDULING...\n");
    int prev = current;

    current++;
    if (current >= NTASKS)
        current = 0;

    uart_puts("\nSCHEDULING...\n");
    context_switch(&tasks[prev], &tasks[current]);
}
