# Firmware for the reduced Ibex demo (RV32I + C, NO M/A extension) on GateMate.
# Produces firmware.vmem (32-bit-word $readmemh format) for SRAMInitFile.
# Toolchain: prefers riscv32-*, falls back to riscv64-* (rv32 multilib).
CROSS  ?= $(shell command -v riscv32-unknown-elf-gcc >/dev/null 2>&1 && echo riscv32-unknown-elf- || echo riscv64-unknown-elf-)
CC      = $(CROSS)gcc
OBJCOPY = $(CROSS)objcopy
OBJDUMP = $(CROSS)objdump

# Core is RV32MNone: rv32i + compressed + Zicsr/Zifencei. NO mul/div (m), NO atomics (a).
ARCH    = -march=rv32ic_zicsr_zifencei -mabi=ilp32
FLAGS   = $(ARCH) -Os -ffreestanding -nostdlib -ffunction-sections -fdata-sections -Wall -Wextra
LDFLAGS = -Wl,--gc-sections -Wl,-Map=firmware.map -T link.ld

OBJS = startup.o main.o uart.o demo_system.o

# yosys-slang can't use $readmemh, so we bake the firmware as an SV declaration
# initializer (../DesignSources/firmware_mem_init.svh) that synth picks up.
INIT_SVH = ../DesignSources/firmware_mem_init.svh

all: $(INIT_SVH)

$(INIT_SVH): firmware.bin bin2svh.py
	python3 bin2svh.py firmware.bin $(INIT_SVH)

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary firmware.elf firmware.bin

firmware.elf: $(OBJS) link.ld
	$(CC) $(FLAGS) $(LDFLAGS) $(OBJS) -o firmware.elf

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(FLAGS) -c $< -o $@

objdump: firmware.elf
	$(OBJDUMP) -d firmware.elf

clean:
	rm -f *.o firmware.elf firmware.bin firmware.vmem firmware.map *.hex

.PHONY: all objdump clean
