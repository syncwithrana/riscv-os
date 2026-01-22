#ifndef IRQ_H
#define IRQ_H

unsigned int irq_disable(void);
void irq_restore(unsigned int flags);

#endif
