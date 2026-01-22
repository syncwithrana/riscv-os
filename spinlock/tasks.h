#ifndef TASKS_H
#define TASKS_H

#include "context.h"

#define MAX_TASKS 4
#define STACK_SIZE 1024

enum task_state {
    TASK_RUNNABLE,
    TASK_SLEEPING,
};

struct task {
    struct context ctx;   // Context (saved registers)
    unsigned char stack[STACK_SIZE]; // Stack for this task

    enum task_state state;
    unsigned int wakeup_tick;
};

extern struct task tasks[MAX_TASKS];
extern volatile unsigned int ticks;

void init_task(int id, void (*fn)(void));
void start_scheduler(void);
void schedule(void);
void sleep(unsigned int n);
void task_tick(void);

// Task entry wrapper
void task_entry(void (*fn)(void));

// Example tasks
void taskA(void);
void taskB(void);
void taskC(void);
void idle_task(void);

#endif
