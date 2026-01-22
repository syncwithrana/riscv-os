.section .text
.globl _start

_start:
    # Setup stack for the boot/kernel thread
    la sp, stack_top
    
    # Disable interrupts initially
    csrw mie, zero

    # Setup trap vector
    la t0, trap_entry
    csrw mtvec, t0

    # Enable Machine External and Timer Interrupts in MIE
    # Bit 11 (MEIE) | Bit 7 (MTIE) | Bit 3 (MSIE)
    li t0, 0x888 
    csrw mie, t0

    # Enable global interrupts (MIE bit in mstatus)
    li t0, 0x8
    csrs mstatus, t0

    # Jump to C code
    call main

hang:
    j hang

.section .bss
.align 4
    .space 4096 # 4KB Boot Stack
stack_top:
