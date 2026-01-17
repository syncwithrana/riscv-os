#include "context.h"

#define MAX_TASKS   3
#define STACK_SIZE  1024

extern void context_switch(struct context *, struct context *);

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
    while (1) {
        asm volatile ("nop");   /* breakpoint A */
        yield();
    }
}

void taskB(void)
{
    while (1) {
        asm volatile ("nop");   /* breakpoint B */
        yield();
    }
}

void taskC(void)
{
    while (1) {
        asm volatile ("nop");   /* breakpoint C */
        yield();
    }
}

/* -------------------------------------------------- */
/* Context initialization                             */
/* -------------------------------------------------- */

void init_context(int id, void (*fn)(void))
{
    tasks[id].ra = (unsigned int)fn;
    tasks[id].sp = (unsigned int)(stacks[id] + STACK_SIZE);
}

/* -------------------------------------------------- */
/* Cooperative scheduler                              */
/* -------------------------------------------------- */

void yield(void)
{
    int prev = current;

    current++;
    if (current >= num_tasks)
        current = 0;

    context_switch(&tasks[prev], &tasks[current]);
}

/* -------------------------------------------------- */
/* Kernel entry                                       */
/* -------------------------------------------------- */

void main(void)
{
    init_context(0, taskA);
    init_context(1, taskB);
    init_context(2, taskC);

    current = 0;

    /* Jump into the first task */
    context_switch(&(struct context){0}, &tasks[0]);

    while (1);
}
