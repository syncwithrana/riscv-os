#include "tasks.h"
#include "context.h"
#include "uart.h"
#include "timer.h"
#include "irq.h"

struct task tasks[MAX_TASKS];
volatile unsigned int ticks = 0;

int current_task = -1;

void task_entry(void (*fn)(void))
{
    // Enable interrupts in mstatus so this task can be preempted!
    irq_enable();
    
    fn();
    
    // Fallback if task returns
    while(1);
}

void init_task(int id, void (*fn)(void))
{
    // Point ra to task_entry wrapper
    tasks[id].ctx.ra = (unsigned int)task_entry;
    
    // sp points to top of stack (stack grows down)
    tasks[id].ctx.sp = (unsigned int)(tasks[id].stack + STACK_SIZE);
    
    // a0 gets the function pointer (argument to task_entry)
    tasks[id].ctx.a0 = (unsigned int)fn;
    
    // initial state
    tasks[id].state = TASK_RUNNABLE;
    tasks[id].wakeup_tick = 0;
}

// Called from timer interrupt
void task_tick(void)
{
    ticks++;

    // Wake up sleeping tasks
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].state == TASK_SLEEPING &&
            tasks[i].wakeup_tick <= ticks) {
            tasks[i].state = TASK_RUNNABLE;
        }
    }
    
    schedule();
}

void schedule(void)
{
    int prev = current_task;
    int next = prev;
    int found = 0;

    // Round-robin to find next RUNNABLE task
    // Start checking from next task
    for (int i = 0; i < MAX_TASKS; i++) {
        next = (next + 1) % MAX_TASKS;
        if (tasks[next].state == TASK_RUNNABLE) {
            found = 1;
            break;
        }
    }

    if (!found) {
        // Should not happen if we have an idle task, 
        // but if it does, stay on current (or idle)
        // If current is sleeping (and was the only one), we might have an issue
        // But we ensure at least one task is runnable (idle task)
        return; 
    }
    
    current_task = next;

    if (prev != -1 && prev != current_task) {
        context_switch(&tasks[prev].ctx, &tasks[current_task].ctx);
    } else if (prev == -1) {
         // Startup: just switch to the first task
         // We need a dummy old context for the first switch
         // But start_scheduler handles this differently usually.
         // Wait, start_scheduler calls context_switch(&dummy, &tasks[0]);
         // Here we are called from interrupt.
    }
}

void start_scheduler(void)
{
    // We assume task 0 is the first one to run, or we pick one.
    // Let's pick the first runnable one.
    int i;
    for(i=0; i<MAX_TASKS; i++){
        if(tasks[i].state == TASK_RUNNABLE){
            current_task = i;
            break;
        }
    }
    
    struct context dummy;
    context_switch(&dummy, &tasks[current_task].ctx);
}

void sleep(unsigned int n)
{
    unsigned int flags = irq_disable(); // Critical section

    tasks[current_task].state = TASK_SLEEPING;
    tasks[current_task].wakeup_tick = ticks + n;

    irq_restore(flags);

    // Yield control
    // We can just wait for next timer interrupt to switch us out, 
    // OR we can force a schedule.
    // If we just return, we are still running but marked SLEEPING.
    // The next timer tick will switch us out.
    // Better to yield immediately.
    // To yield immediately, we need a way to trigger schedule synchronously
    // or wait.
    
    // For this simple OS, we can busy wait for the timer to context switch us?
    // No, that wastes CPU.
    // We should call schedule() ourselves?
    // If we call schedule(), it will switch context.
    // But schedule() expects to be called?
    
    // We need to trigger the switch.
    // Let's assume we can call an assembly trap/yield
    // Or just call schedule() directly if we are in thread context?
    // Yes, we can call schedule().
    
    // NOTE: schedule() performs context_switch.
    // context_switch saves current context (at the call site) and loads new.
    // So when we resume, we return from schedule().
    
    schedule();
}

void idle_task(void)
{
    while(1) {
        // Just wait for interrupts
        // asm volatile("wfi"); // Optional power saving
    }
}

void taskA(void)
{
    while (1) {
        uart_putc('A');
        sleep(20);
    }
}

void taskB(void)
{
    while (1) {
        uart_putc('B');
        sleep(40);
    }
}

void taskC(void)
{
    while (1) {
        uart_putc('C');
        sleep(60);
    }
}
