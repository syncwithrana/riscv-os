# ---------- Root Makefile ----------

# Toolchain
RISCV_PREFIX = riscv32-unknown-elf
CC  = $(RISCV_PREFIX)-gcc
LD  = $(RISCV_PREFIX)-ld
GDB = $(RISCV_PREFIX)-gdb

# Architecture / Flags
ARCH    = -march=rv32i_zicsr -mabi=ilp32
CFLAGS  = $(ARCH) -ffreestanding -nostdlib -nostartfiles -O0 -g
ASFLAGS = $(CFLAGS)

# Input folder (mandatory)
DIR ?= none

ifeq ($(DIR),none)
$(error Usage: make DIR=<program_folder>)
endif

SRC_DIR   = $(DIR)
BUILD_DIR = build/$(DIR)

# Sources
C_SRCS = $(wildcard $(SRC_DIR)/*.c)
S_SRCS = $(wildcard $(SRC_DIR)/*.s) $(wildcard $(SRC_DIR)/*.S)

# Objects (ONLY .o files)
OBJS = \
	$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS)) \
	$(patsubst $(SRC_DIR)/%.s,$(BUILD_DIR)/%.o,$(filter %.s,$(S_SRCS))) \
	$(patsubst $(SRC_DIR)/%.S,$(BUILD_DIR)/%.o,$(filter %.S,$(S_SRCS)))

# Outputs
ELF    = $(BUILD_DIR)/kernel.elf
LINKER = $(SRC_DIR)/linker.ld
GDBSCR = $(SRC_DIR)/*.gdb

# ---------------- Targets ----------------

all: $(ELF)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile C
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Assembly (.s / .S)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	$(CC) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(ASFLAGS) -c $< -o $@

# Link (OBJECT FILES ONLY)
$(ELF): $(OBJS) $(LINKER)
	$(LD) -T $(LINKER) -o $@ $(OBJS)

# ---------------- Run / Debug ----------------

run: all
	qemu-system-riscv32 \
		-machine virt \
		-nographic \
		-bios none \
		-kernel $(ELF) \
		-S -gdb tcp::1234

gdb:
	$(GDB) -q $(ELF) -x $(GDBSCR)

# ---------------- Process Control ----------------

kill:
	@PIDS=$$(ps aux | grep qemu-system-riscv32 | grep -v grep | awk '{print $$2}'); \
	if [ -z "$$PIDS" ]; then \
		echo "[INFO] QEMU not running"; \
	else \
		echo "[INFO] Killing QEMU PID(s): $$PIDS"; \
		kill $$PIDS || true; \
	fi

kill-force:
	@PIDS=$$(ps aux | grep qemu-system-riscv32 | grep -v grep | awk '{print $$2}'); \
	if [ -n "$$PIDS" ]; then \
		kill -9 $$PIDS || true; \
	fi

rerun: kill all run

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run gdb kill kill-force rerun clean
