#ifndef TIMER_H
#define TIMER_H

/* QEMU / VirtIO / FPGA standard constants for CLINT */
#define CLINT_BASE 0x2000000
#define MTIMECMP   (volatile unsigned long long *)(CLINT_BASE + 0x4000)
#define MTIME      (volatile unsigned long long *)(CLINT_BASE + 0xBFF8)

/* 10MHz assumed clock */
#define TIMER_INTERVAL 10000000

extern volatile int tick_flag;

void timer_init(void);
void timer_handler(void);
void delay(void);

#endif
