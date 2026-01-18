#include "uart.h"
#include "context.h"
#include "tasks.h"
#include "timer.h"

#define MAX_TASKS   3
#define STACK_SIZE  1024

unsigned char stacks[MAX_TASKS][STACK_SIZE] __attribute__((aligned(16)));
struct context tasks[MAX_TASKS];
int current = -1;
int num_tasks = MAX_TASKS;
void schedule(void);

void task_entry(void (*fn)(void))
{
    /* Enable interrupts (MIE bit 3) */
    asm volatile("csrs mstatus, %0" : : "r" (1 << 3));
    
    fn();
}

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

void init_task(int id, void (*fn)(void))
{
    tasks[id].ra = (unsigned int)task_entry;
    tasks[id].sp = (unsigned int)(stacks[id] + STACK_SIZE);
    tasks[id].a0 = (unsigned int)fn;
    tasks[id].mepc = (unsigned int)task_entry;
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