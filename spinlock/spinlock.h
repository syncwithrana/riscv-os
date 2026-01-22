#ifndef SPINLOCK_H
#define SPINLOCK_H

struct spinlock {
    volatile int locked;
};

void spinlock_init(struct spinlock *lk);
void spin_lock(struct spinlock *lk);
void spin_unlock(struct spinlock *lk);

#endif
