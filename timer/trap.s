.section .text
.globl trap_entry

trap_entry:
    addi sp, sp, -16
    sw ra, 12(sp)
    sw t0, 8(sp)
    sw t1, 4(sp)
    sw t2, 0(sp)

    csrr t0, mcause
    li t1, 0x80000007
    beq t0, t1, timer_irq

trap_exit:
    lw ra, 12(sp)
    lw t0, 8(sp)
    lw t1, 4(sp)
    lw t2, 0(sp)
    addi sp, sp, 16
    mret

timer_irq:
    call timer_handler
    j trap_exit
