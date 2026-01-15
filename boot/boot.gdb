target remote :1234
break _start
continue
si
info registers sp
break main
continue
printf "boot_ok = %d\n", boot_ok
next
printf "boot_ok = %d\n", boot_ok
quit