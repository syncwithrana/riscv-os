#include "uart.h"
#include "timer.h"
#include "tasks.h"

void main(void)
{
    uart_puts("Clean Scheduler Starting...\n");
    
    timer_init(); // Verify this primes the timer
    
    // Initialize tasks
    // Task 0 reserved for something? Or just use 0,1,2
    // We defined MAX_TASKS 4
    init_task(0, taskA);
    init_task(1, taskB);
    init_task(2, taskC);
    
    // Task 3 is idle task
    init_task(3, idle_task);
    
    start_scheduler();
    
    while(1);
}
