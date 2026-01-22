.section .text
.globl context_switch

# void context_switch(struct context *old_ctx, struct context *new_ctx);
# a0 = old_ctx
# a1 = new_ctx

context_switch:
    # Save all registers to old_ctx (a0)
    sw ra,   0(a0)
    sw sp,   4(a0)
    sw gp,   8(a0)
    sw tp,  12(a0)
    sw t0,  16(a0)
    sw t1,  20(a0)
    sw t2,  24(a0)
    sw s0,  28(a0)
    sw s1,  32(a0)
    sw a0,  36(a0) # Saving a0 (old_ctx ptr) into itself - mostly for completeness
    sw a1,  40(a0)
    sw a2,  44(a0)
    sw a3,  48(a0)
    sw a4,  52(a0)
    sw a5,  56(a0)
    sw a6,  60(a0)
    sw a7,  64(a0)
    sw s2,  68(a0)
    sw s3,  72(a0)
    sw s4,  76(a0)
    sw s5,  80(a0)
    sw s6,  84(a0)
    sw s7,  88(a0)
    sw s8,  92(a0)
    sw s9,  96(a0)
    sw s10,100(a0)
    sw s11,104(a0)
    sw t3, 108(a0)
    sw t4, 112(a0)
    sw t5, 116(a0)
    sw t6, 120(a0)
    
    # Save mepc (optional for cooperative, but consistent with structure)
    csrr t0, mepc
    sw t0, 124(a0)

    # Load all registers from new_ctx (a1)
    lw ra,   0(a1)
    lw sp,   4(a1)
    lw gp,   8(a1)
    lw tp,  12(a1)
    lw t0,  16(a1)
    lw t1,  20(a1)
    lw t2,  24(a1)
    lw s0,  28(a1)
    lw s1,  32(a1)
    
    # Skip a0, a1 for now, load others
    lw a2,  44(a1)
    lw a3,  48(a1)
    lw a4,  52(a1)
    lw a5,  56(a1)
    lw a6,  60(a1)
    lw a7,  64(a1)
    lw s2,  68(a1)
    lw s3,  72(a1)
    lw s4,  76(a1)
    lw s5,  80(a1)
    lw s6,  84(a1)
    lw s7,  88(a1)
    lw s8,  92(a1)
    lw s9,  96(a1)
    lw s10,100(a1)
    lw s11,104(a1)
    lw t3, 108(a1)
    lw t4, 112(a1)
    lw t5, 116(a1)
    lw t6, 120(a1)
    
    # Load mepc (if we were preempted, this restores PC)
    lw t0, 124(a1)
    csrw mepc, t0

    # Finally load a0/a1
    lw a0,  36(a1)
    lw a1,  40(a1)

    ret
