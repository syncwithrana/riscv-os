CROSS_COMPILE = riscv32-unknown-elf-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

CFLAGS = -march=rv32i_zicsr -mabi=ilp32 -ffreestanding -nostdlib -nostartfiles -O0 -g
LDFLAGS = -T linker.ld

BUILD_DIR = build
OBJS = $(BUILD_DIR)/start.o $(BUILD_DIR)/main.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/trap.o \
       $(BUILD_DIR)/context.o $(BUILD_DIR)/timer.o $(BUILD_DIR)/tasks.o $(BUILD_DIR)/irq.o

all: $(BUILD_DIR)/kernel.elf

$(BUILD_DIR)/kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(BUILD_DIR)/kernel.elf
	qemu-system-riscv32 -M virt -bios none -kernel $(BUILD_DIR)/kernel.elf -nographic

clean:
	rm -rf $(BUILD_DIR)
