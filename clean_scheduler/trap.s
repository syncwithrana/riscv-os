.section .text
.globl trap_entry

.align 4
trap_entry:
    # 1. Swap sp with mscratch. 
    # If mscratch is 0 (first time or nested?), this might overwrite.
    # But usually mscratch points to task struct or kernel stack.
    # For simplicity here: use the current stack.
    # We allocate a frame on the *current* task stack.
    addi sp, sp, -128

    # 2. Save registers that C handler might clobber
    # For a full preemptive scheduler, we might want to save EVERYTHING 
    # if we treat this as a potential context switch point.
    # Since schedule() calls context_switch internally, 
    # context_switch will do the FULL save to the task struct.
    # BUT, to call schedule(), we need a valid C environment.
    # So we save Caller-Saved registers + arguments.
    
    sw ra, 0(sp)
    sw t0, 4(sp)
    sw t1, 8(sp)
    sw t2, 12(sp)
    sw a0, 16(sp)
    sw a1, 20(sp)
    sw a2, 24(sp)
    sw a3, 28(sp)
    sw a4, 32(sp)
    sw a5, 36(sp)
    sw a6, 40(sp)
    sw a7, 44(sp)
    sw t3, 48(sp)
    sw t4, 52(sp)
    sw t5, 56(sp)
    sw t6, 60(sp)
    
    # Save mepc
    csrr t0, mepc
    sw t0, 64(sp)

    # 3. Call C handler
    call trap_handler

    # 4. Restore mepc
    lw t0, 64(sp)
    csrw mepc, t0

    # 5. Restore registers
    lw ra, 0(sp)
    lw t0, 4(sp)
    lw t1, 8(sp)
    lw t2, 12(sp)
    lw a0, 16(sp)
    lw a1, 20(sp)
    lw a2, 24(sp)
    lw a3, 28(sp)
    lw a4, 32(sp)
    lw a5, 36(sp)
    lw a6, 40(sp)
    lw a7, 44(sp)
    lw t3, 48(sp)
    lw t4, 52(sp)
    lw t5, 56(sp)
    lw t6, 60(sp)

    addi sp, sp, 128
    mret
