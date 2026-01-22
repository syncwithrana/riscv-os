#ifndef IRQ_H
#define IRQ_H

static inline unsigned int irq_disable(void)
{
    unsigned int mstatus;
    asm volatile("csrr %0, mstatus" : "=r"(mstatus));
    asm volatile("csrc mstatus, %0" : : "r"(1 << 3)); // Clear MIE (bit 3)
    return mstatus;
}

static inline void irq_restore(unsigned int flags)
{
    // Restore MIE bit from saved flags
    if (flags & (1 << 3)) {
        asm volatile("csrs mstatus, %0" : : "r"(1 << 3));
    } else {
        asm volatile("csrc mstatus, %0" : : "r"(1 << 3));
    }
}

static inline void irq_enable(void)
{
    asm volatile("csrs mstatus, %0" : : "r"(1 << 3)); // Set MIE
}

#endif
