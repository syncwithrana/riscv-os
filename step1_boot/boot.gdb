# ---------- boot.gdb (AUTO, WORKFLOW-2) ----------

set pagination off
set confirm off
set verbose off
set breakpoint pending on

echo \n===== RISC-V OS BOOT DEBUG (AUTO) =====\n

target remote :1234
set architecture riscv:rv32

# Break at _start
break _start
commands
    silent
    echo \n--- Hit _start (Machine mode) ---\n
    info registers pc sp
    x/4i $pc
    continue
end

# Break at kernel_main
break kernel_main
commands
    silent
    echo \n--- Entered kernel_main (Supervisor mode) ---\n
    info registers pc sp
    echo \n--- sstatus ---\n
    p/x $sstatus
    x/4i $pc
    echo \n===== BOOT VERIFIED =====\n
    quit
end

continue
