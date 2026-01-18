CROSS = riscv32-unknown-elf-

CC = $(CROSS)gcc
LD = $(CROSS)ld

CFLAGS = -march=rv32i_zicsr -mabi=ilp32 \
         -ffreestanding -nostdlib -nostartfiles\
         -O0 -g

all: kernel.elf

kernel.elf: start.o main.o context.o trap.o uart.o
	$(LD) -T linker.ld -o $@ $^

start.o: start.s
	$(CC) $(CFLAGS) -c $<

context.o: context.s
	$(CC) $(CFLAGS) -c $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

trap.o: trap.s
	$(CC) $(CFLAGS) -c $<

uart.o: uart.c
	$(CC) $(CFLAGS) -c $<

run:
	qemu-system-riscv32 -machine virt -nographic -bios none -kernel kernel.elf

debug:
	qemu-system-riscv32 -machine virt -nographic \
		-bios none -kernel kernel.elf -s -S

gdb:
	$(CROSS)gdb -ex "target remote :1234" -q kernel.elf

clean:
	rm -f *.o *.elf
