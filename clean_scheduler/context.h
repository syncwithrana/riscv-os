#ifndef CONTEXT_H
#define CONTEXT_H

struct context {
    unsigned int ra;
    unsigned int sp;
    unsigned int gp;
    unsigned int tp;
    unsigned int t0;
    unsigned int t1;
    unsigned int t2;
    unsigned int s0;
    unsigned int s1;
    unsigned int a0;
    unsigned int a1;
    unsigned int a2;
    unsigned int a3;
    unsigned int a4;
    unsigned int a5;
    unsigned int a6;
    unsigned int a7;
    unsigned int s2;
    unsigned int s3;
    unsigned int s4;
    unsigned int s5;
    unsigned int s6;
    unsigned int s7;
    unsigned int s8;
    unsigned int s9;
    unsigned int s10;
    unsigned int s11;
    unsigned int t3;
    unsigned int t4;
    unsigned int t5;
    unsigned int t6;
    unsigned int mepc; // Saved PC for trap return
};

extern void context_switch(struct context *old_ctx, struct context *new_ctx);

#endif
