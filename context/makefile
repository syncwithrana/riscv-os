CROSS = riscv32-unknown-elf-

CC = $(CROSS)gcc
LD = $(CROSS)ld

CFLAGS = -march=rv32i -mabi=ilp32 \
         -ffreestanding -nostdlib -nostartfiles\
         -O0 -g

all: kernel.elf

kernel.elf: start.o main.o context.o
	$(LD) -T linker.ld -o $@ $^

start.o: start.s
	$(CC) $(CFLAGS) -c $<

context.o: context.s
	$(CC) $(CFLAGS) -c $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

run:
	qemu-system-riscv32 -machine virt -nographic -kernel kernel.elf

debug:
	qemu-system-riscv32 -machine virt -nographic \
		-bios none -kernel kernel.elf -s -S

clean:
	rm -f *.o *.elf
