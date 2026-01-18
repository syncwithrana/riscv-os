.section .text
.globl _start

_start:
    la sp, stack_top

    la t0, trap_entry
    csrw mtvec, t0

    li t0, (1 << 7)      /* MTIE */
    csrs mie, t0

    li t0, (1 << 3)      /* MIE */
    csrs mstatus, t0

    call main

hang:
    j hang

.section .bss
.align 16
stack:
    .space 4096
stack_top:
