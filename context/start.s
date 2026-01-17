.section .text
.globl _start

_start:
    la sp, stack_top
    call main

hang:
    j hang

.section .bss
.align 16
stack:
    .space 4096
stack_top:
