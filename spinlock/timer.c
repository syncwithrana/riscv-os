#include "timer.h"
#include "uart.h"
#include "tasks.h"

volatile int tick_flag = 1;

void timer_init(void)
{
    // 0x100000 is approx 1,000,000. 
    // At 10MHz, this is 0.1 seconds (10Hz).
    unsigned long long next = *MTIME + 1000000;
    
    *MTIMECMP = next;
}

void delay(void)
{
    // Basic spin wait
    volatile int i;
    for (i = 0; i < 1000000; i++);
}

// Called from trap.s
void trap_handler(void)
{
    unsigned int mcause;
    asm volatile("csrr %0, mcause" : "=r"(mcause));

    if ((mcause & 0x80000007) == 0x80000007) {
        // uart_putc('T'); // Removed debug output
        tick_flag = 1;
        timer_init(); // Ack/Rearm
        task_tick();  // Update ticks and schedule
    }
}
