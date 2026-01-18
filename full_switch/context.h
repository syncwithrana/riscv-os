struct context {
    unsigned int ra;
    unsigned int sp;
    unsigned int gp;
    unsigned int tp;

    unsigned int t0, t1, t2;
    unsigned int s0, s1;
    unsigned int a0, a1, a2, a3, a4, a5, a6, a7;
    unsigned int s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    unsigned int t3, t4, t5, t6;

    unsigned int mepc;
};

extern void context_switch(struct context *, struct context *);