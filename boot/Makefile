CROSS = riscv32-unknown-elf-

CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump

CFLAGS = -march=rv32i -mabi=ilp32 \
         -ffreestanding -nostdlib -nostartfiles -O0 -g

all: kernel.elf

kernel.elf: start.o main.o
	$(LD) -T linker.ld -o $@ $^

start.o: start.s
	$(CC) $(CFLAGS) -c start.s

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

run:
	qemu-system-riscv32 \
		-machine virt \
		-nographic \
		-kernel kernel.elf

debug:
	qemu-system-riscv32 \
		-machine virt \
		-nographic \
		-bios none \
		-kernel kernel.elf \
		-s -S

clean:
	rm -f *.o *.elf
