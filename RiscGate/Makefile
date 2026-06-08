PREFIX := DesignSources/
DESIGN_SOURCES := $(addprefix $(PREFIX),$(shell cat compile_files.txt))
PRIMITIVE_SOURCES := $(addprefix $(PREFIX),$(shell cat primitive_files.txt))
BLACK_BOX_CC_PLL = DesignSources/cc_pll_bb.sv
#INCLUDE_FILES := $(addprefix $(PREFIX),$(shell cat sv_headers.txt))
TOP = top_gatemate
SLANG_PLUGIN = /home/xaver/yosys-slang/build/slang.so
synth:
	yosys -m slang -p "read_slang --std latest --ignore-initial $(DESIGN_SOURCES) DesignSources/cells_sim.v --top $(TOP) -D SYNTHESIS; synth_gatemate -top $(TOP) -luttree -nomx8; write_verilog $(TOP)_synth.v; write_json $(TOP)_synth_final.json" > synth.log

clean:
	rm *.log *.png *.v *.json impl.txt impl.bit

implement:
	nextpnr-himbaechel -l routing.log --device=CCGM1A1 --vopt allow-unconstrained --json $(TOP)_synth_final.json -o ccf=pin_constraints.ccf -o out=impl.txt --sdc timing_constraints.sdc --router router2

bitfile:
	gmpack impl.txt impl.bit

clk_test:
	yosys -p "read_verilog -sv DesignSources/clkgen_gatemate.sv; synth_gatemate -top clkgen_gatemate -luttree -nomx8; write_verilog clkgen_gatemate_synth.v; write_json clkgen_gatemate_final_synth.json"  

synth_no_slang:
	yosys -p "read_verilog -sv -formal $(DESIGN_SOURCES); synth_gatemate -top $(TOP) -luttree -nomx8; write_verilog $(TOP)_synth.v; write_json $(TOP)_synth_final.json"