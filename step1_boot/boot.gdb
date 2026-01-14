# ---------- boot.gdb (FINAL, FULL AUTO) ----------

set pagination off
set confirm off
set verbose off
set breakpoint pending on

echo \n===== RISC-V OS BOOT DEBUG (AUTO) =====\n

# Connect to QEMU (QEMU must already be running with -S)
target remote :1234

# Set architecture after connect
set architecture riscv:rv32

# --------------------------------------------------
# Break at _start (Machine mode)
# --------------------------------------------------
break _start
commands
    silent
    echo \n--- Hit _start (Machine mode) ---\n
    info registers pc sp
    x/6i $pc
    continue
end

# --------------------------------------------------
# Break at kernel_main (Supervisor mode)
# --------------------------------------------------
break kernel_main
commands
    silent
    echo \n--- Entered kernel_main (Supervisor mode) ---\n
    info registers pc sp
    echo \n--- sstatus ---\n
    p/x $sstatus
    x/6i $pc
    echo \n===== BOOT SEQUENCE VERIFIED =====\n
    quit
end

# --------------------------------------------------
# IMPORTANT: start execution
# --------------------------------------------------
continue
