.section .text
.globl _start

_start:
    # Setup stack
    la sp, stack_top

    # Zero BSS
    la t0, __bss_start
    la t1, __bss_end
zero_bss:
    bge t0, t1, done_bss
    sw zero, 0(t0)
    addi t0, t0, 4
    j zero_bss
done_bss:

    # Set MPP = Supervisor
    csrr t0, mstatus
    li   t1, ~(3 << 11)
    and  t0, t0, t1
    li   t1, (1 << 11)     # MPP = S
    or   t0, t0, t1
    csrw mstatus, t0

    # Set mepc = kernel_main
    la t0, kernel_main
    csrw mepc, t0

    # Disable paging for now
    csrw satp, zero

    # Enter S-mode
    mret

.section .bss
.align 12
stack:
    .space 4096
stack_top:
