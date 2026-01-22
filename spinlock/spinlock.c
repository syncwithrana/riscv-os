#include "spinlock.h"
#include "irq.h"

/* atomic exchange */
static inline int xchg(volatile int *addr, int newval)
{
    int old;
    asm volatile(
        "amoswap.w %0, %2, (%1)"
        : "=r"(old)
        : "r"(addr), "r"(newval)
        : "memory"
    );
    return old;
}

void spinlock_init(struct spinlock *lk)
{
    lk->locked = 0;
}

void spin_lock(struct spinlock *lk)
{
    unsigned int flags = irq_disable();

    while (xchg(&lk->locked, 1) != 0)
        ;   // spin

    /* lock acquired */
    asm volatile("" ::: "memory");

    /* interrupts stay disabled while holding lock */
    lk->locked |= (flags << 1);   // optional bookkeeping
}

void spin_unlock(struct spinlock *lk)
{
    asm volatile("" ::: "memory");

    lk->locked = 0;

    irq_restore(lk->locked >> 1); // restore irq flags if saved
}
