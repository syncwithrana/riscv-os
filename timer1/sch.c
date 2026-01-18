#include "uart.h"
#include "context.h"
#include "tasks.h"

#define MAX_TASKS   3
#define STACK_SIZE  1024

/* -------------------------------------------------- */
/* Per-task stacks                                    */
/* -------------------------------------------------- */
unsigned char stacks[MAX_TASKS][STACK_SIZE];

/* -------------------------------------------------- */
/* Task contexts                                      */
/* -------------------------------------------------- */
struct context tasks[MAX_TASKS];

/* -------------------------------------------------- */
/* Scheduler state                                    */
/* -------------------------------------------------- */
int current = -1;
int num_tasks = MAX_TASKS;

/* -------------------------------------------------- */
/* Forward declarations                               */
/* -------------------------------------------------- */
void yield(void);

/* -------------------------------------------------- */
/* Tasks                                              */
/* -------------------------------------------------- */

void taskA(void)
{
    uart_putc('A');
    while (1) {
        asm volatile ("nop");   /* breakpoint A */
        yield();
    }
}

void taskB(void)
{
    uart_putc('B');
    while (1) {
        asm volatile ("nop");   /* breakpoint B */
        yield();
    }
}

void taskC(void)
{
    uart_putc('C');
    while (1) {
        asm volatile ("nop");   /* breakpoint C */
        yield();
    }
}

/* -------------------------------------------------- */
/* Context initialization                             */
/* -------------------------------------------------- */

void init_task(int id, void (*fn)(void))
{
    tasks[id].ra = (unsigned int)fn;
    tasks[id].sp = (unsigned int)(stacks[id] + STACK_SIZE);
}

/* -------------------------------------------------- */
/* Cooperative scheduler                              */
/* -------------------------------------------------- */

void task_switch(void)
{
    current = 0;
    context_switch(&(struct context){0}, &tasks[0]);
}


void yield(void)
{
    int prev = current;

    current++;
    if (current >= num_tasks)
        current = 0;

    context_switch(&tasks[prev], &tasks[current]);
}