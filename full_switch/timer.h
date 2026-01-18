#define MTIMECMP_LO (*(volatile unsigned int *)0x02004000)
#define MTIMECMP_HI (*(volatile unsigned int *)0x02004004)
#define MTIME_LO    (*(volatile unsigned int *)0x0200BFF8)
#define MTIME_HI    (*(volatile unsigned int *)0x0200BFFC)

void timer_init(void);
void timer_handler(void);
void delays(void);
