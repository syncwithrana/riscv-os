#ifndef TASKS_H
#define TASKS_H

#define MAX_TASKS 4
#define STACK_SIZE 1024

void init_task(int id, void (*fn)(void));
void start_scheduler(void);
void schedule(void);

// Task entry wrapper
void task_entry(void (*fn)(void));

// Example tasks
void taskA(void);
void taskB(void);
void taskC(void);

#endif
