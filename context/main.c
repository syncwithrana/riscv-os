#include "context.h"

extern void context_switch(struct context *, struct context *);

unsigned char stack1[1024];
unsigned char stack2[1024];

struct context ctx1;
struct context ctx2;
struct context *current;

void yield(void);

/* Task 1 */
void task1(void)
{
    while (1) {
        asm volatile ("nop");  // breakpoint here
        yield();
    }
}

/* Task 2 */
void task2(void)
{
    while (1) {
        asm volatile ("nop");  // breakpoint here
        yield();
    }
}

void init_context(struct context *ctx, void (*fn)(void), unsigned char *stack)
{
    ctx->ra = (unsigned int)fn;
    ctx->sp = (unsigned int)(stack + 1024);
}

void yield(void)
{
    if (current == &ctx1) {
        current = &ctx2;
        context_switch(&ctx1, &ctx2);
    } else {
        current = &ctx1;
        context_switch(&ctx2, &ctx1);
    }
}

void main(void)
{
    init_context(&ctx1, task1, stack1);
    init_context(&ctx2, task2, stack2);

    current = &ctx1;

    /* jump into first task */
    context_switch(&(struct context){0}, &ctx1);

    while (1);
}
