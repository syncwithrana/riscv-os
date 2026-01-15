ENTRY(_start)

SECTIONS
{
  /* QEMU virt machine RAM starts here */
  . = 0x80000000;

  .text : {
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    *(.bss*)
    *(COMMON)
  }
}
