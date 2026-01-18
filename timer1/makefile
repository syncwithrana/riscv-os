CROSS = riscv32-unknown-elf-
CC = $(CROSS)gcc
LD = $(CROSS)ld

CFLAGS = -march=rv32i_zicsr -mabi=ilp32 \
         -ffreestanding -nostdlib -nostartfiles -O0 -g

all: kernel.elf

kernel.elf: start.o main.o uart.o trap.o context.o timer.o sch.o
	$(LD) -T linker.ld -o $@ $^

start.o: start.s
	$(CC) $(CFLAGS) -c start.s

trap.o: trap.s
	$(CC) $(CFLAGS) -c trap.s

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

uart.o: uart.c
	$(CC) $(CFLAGS) -c uart.c

context.o: context.s
	$(CC) $(CFLAGS) -c context.s

timer.o: timer.c
	$(CC) $(CFLAGS) -c timer.c

tasks.o: tasks.c
	$(CC) $(CFLAGS) -c tasks.c

sch.o: sch.c
	$(CC) $(CFLAGS) -c sch.c

run:
	qemu-system-riscv32 \
		-machine virt \
		-nographic \
		-bios none \
		-kernel kernel.elf

clean:
	rm -f *.o *.elf
