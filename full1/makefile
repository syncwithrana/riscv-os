CROSS = riscv32-unknown-elf-
CC = $(CROSS)gcc
LD = $(CROSS)ld

CFLAGS = -march=rv32i_zicsr -mabi=ilp32 \
         -ffreestanding -nostdlib -nostartfiles -O0 -g

all: kernel.elf

kernel.elf: start.o trap.o uart.o main.o string.o
	$(LD) -T linker.ld -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.s
	$(CC) $(CFLAGS) -c $<

run:
	qemu-system-riscv32 -machine virt -nographic -bios none -kernel kernel.elf

clean:
	rm -f *.o *.elf
