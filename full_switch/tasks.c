#include "uart.h"
#include "context.h"
#include "tasks.h"
#include "timer.h"

#define MAX_TASKS   3
#define STACK_SIZE  1024

unsigned char stacks[MAX_TASKS][STACK_SIZE];
struct context tasks[MAX_TASKS];
int current = -1;
int num_tasks = MAX_TASKS;
void schedule(void);

void taskA(void)
{
    while (1) {
        delays();
        uart_putc('A');
        schedule();
    }
}

void taskB(void)
{
    while (1) {
        delays();
        uart_putc('B');
        schedule();
    }
}

void taskC(void)
{
    while (1) {
        delays();
        uart_putc('C');
        schedule();
    }
}

void init_task(int id, void (*fn)(void))
{
    tasks[id].ra = (unsigned int)fn;
    tasks[id].sp = (unsigned int)(stacks[id] + STACK_SIZE);
    tasks[id].mepc = (unsigned int)fn;
}

void start_task(void)
{
    current = 0;
    context_switch(&(struct context){0}, &tasks[0]);
}

void schedule(void)
{
    int prev = current;
    current++;
    if (current >= num_tasks)
        current = 0;

    context_switch(&tasks[prev], &tasks[current]);
}