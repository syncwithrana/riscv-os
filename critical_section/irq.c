#include "irq.h"

/*
 * Disable interrupts and return previous mstatus
 */
unsigned int irq_disable(void)
{
    unsigned int flags;

    asm volatile(
        "csrr %0, mstatus\n"   /* read mstatus */
        "csrc mstatus, %1\n"   /* clear MIE */
        : "=r"(flags)
        : "r"(1 << 3)
        : "memory"
    );

    return flags;
}

/*
 * Restore previous interrupt state
 */
void irq_restore(unsigned int flags)
{
    asm volatile(
        "csrw mstatus, %0\n"
        :
        : "r"(flags)
        : "memory"
    );
}
