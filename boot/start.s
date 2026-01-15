.section .text
.globl _start

_start:
    /* set stack pointer */
    la sp, stack_top

    /* jump to C */
    call main

hang:
    j hang


.section .bss
.align 16
stack:
    .space 4096
stack_top:
