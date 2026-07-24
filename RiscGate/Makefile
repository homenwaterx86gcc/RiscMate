PREFIX := DesignSources/
DESIGN_SOURCES := $(addprefix $(PREFIX),$(shell cat compile_files.txt))
PRIMITIVE_SOURCES := $(addprefix $(PREFIX),$(shell cat primitive_files.txt))
BLACK_BOX_CC_PLL = DesignSources/cc_pll_bb.sv
ROUTING_LOG_FILE = Logs/routing.log
IMPLEMENT_FLAGS = -l $(ROUTING_LOG_FILE) --seed 1 --verbose --device=CCGM1A1 --vopt allow-unconstrained --json Synth/$(TOP)_synth_final.json
GATE_MATE_PIN_CONSTRAINTS = Constraints/pin_constraints.ccf
GATE_MATE_TIMING_CONSTRAINTS = Constraints/timing_constraints.sdc
#INCLUDE_FILES := $(addprefix $(PREFIX),$(shell cat sv_headers.txt))
TOP = top_gatemate
SLANG_PLUGIN = /home/xaver/yosys-slang/build/slang.so
synth:
	yosys -m slang -p "read_slang --std latest --ignore-initial $(DESIGN_SOURCES) DesignSources/cells_sim.v --top $(TOP) -D SYNTHESIS; synth_gatemate -top $(TOP) -luttree -nomx8; write_verilog Synth/$(TOP)_synth.v; write_json Synth/$(TOP)_synth_final.json" > Logs/synth.log

clean:
	rm *.log *.png Synth/*.v Synth/*.json impl.txt impl.bit Logs/*.log

implement_constrained:
	nextpnr-himbaechel $(IMPLEMENT_FLAGS) -o ccf=$(GATE_MATE_PIN_CONSTRAINTS) -o out=impl.txt --sdc $(GATE_MATE_TIMING_CONSTRAINTS) --router router2
implement_nopins:
	nextpnr-himbaechel $(IMPLEMENT_FLAGS) -o out=Impl/impl.txt --sdc $(GATE_MATE_TIMING_CONSTRAINTS) --router router2
bitfile:
	gmpack Impl/impl.txt Impl/impl.bit

clk_test:
	yosys -p "read_verilog -sv DesignSources/clkgen_gatemate.sv; synth_gatemate -top clkgen_gatemate -luttree -nomx8; write_verilog clkgen_gatemate_synth.v; write_json clkgen_gatemate_final_synth.json"  

synth_no_slang:
	yosys -p "read_verilog -sv -formal $(DESIGN_SOURCES); synth_gatemate -top $(TOP) -luttree -nomx8; write_verilog $(TOP)_synth.v; write_json $(TOP)_synth_final.json"

complete:
	make -C C clean
	make -C C 
	python3 C/bin2svh.py C/firmware.bin DesignSources/firmware_mem_init.svh
	rm -f .log.png Synth/.v Synth/.json Impl/impl.txt Impl/impl.bit Logs/*.log
	yosys -m slang -p "read_slang --std latest --ignore-initial $(DESIGN_SOURCES) --top $(TOP) -D SYNTHESIS; synth_gatemate -top $(TOP) -luttree -nomx8; write_verilog Synth/$(TOP)_synth.v; write_json Synth/$(TOP)_synth_final.json" > Logs/synth.log
	nextpnr-himbaechel $(IMPLEMENT_FLAGS) -o ccf=$(GATE_MATE_PIN_CONSTRAINTS) -o out=Impl/impl.txt --sdc $(GATE_MATE_TIMING_CONSTRAINTS) --router router2
	gmpack Impl/impl.txt Impl/impl.bit
	sudo /home/kasachstan_horse67/toolchains/oss-cad-suite/bin/openFPGALoader -c dirtyJtag Impl/impl.bit