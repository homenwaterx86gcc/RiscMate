COMPILER = riscv32-unknown-elf-gcc
FLAGS = -march=rv32imc -mabi=ilp32 -nostdlib -Wall -Wextra

all: firmware.bin

firmware.bin:firmware.elf
	riscv32-unknown-elf-objcopy -O ihex firmware.elf firmware.hex

firmware.elf: main.o startup.o uart.o demo_system.o
	$(COMPILER) $(FLAGS) -T link.ld startup.o uart.o demo_system.o main.o -o firmware.elf

main.o: main.c 
	$(COMPILER) $(FLAGS) -c main.c -o main.o

startup.o: startup.S 
	$(COMPILER) $(FLAGS) -c startup.S -o startup.o


uart.o: uart.c 
	$(COMPILER) $(FLAGS) -c uart.c -o uart.o
	
demo_system.o: demo_system.c
	$(COMPILER) $(FLAGS) -c demo_system.c -o demo_system.o
clean:
	rm main.o firmware.elf *.fst *.log *.csv

objdump:
	riscv32-unknown-elf-objdump -d firmware.elf

# Firmware image for synthesis: bake the .bin into a SystemVerilog array
# initializer that the RAM picks up (yosys-slang cannot do $readmemh).
../DesignSources/firmware_mem_init.svh: firmware.bin bin2svh.py
	python3 bin2svh.py firmware.bin $@

svh: ../DesignSources/firmware_mem_init.svh
