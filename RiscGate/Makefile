PREFIX := DesignSources/
DESIGN_SOURCES := $(addprefix $(PREFIX),$(shell cat compile_files.txt))
#INCLUDE_FILES := $(addprefix $(PREFIX),$(shell cat sv_headers.txt))
TOP = top_gatemate
SLANG_PLUGIN = /home/xaver/yosys-slang/build/slang.so
synth:
	yosys -m slang -p "read_slang --std latest --ignore-initial $(DESIGN_SOURCES) --top $(TOP) -D SYNTHESIS; synth_gatemate -top $(TOP) -luttree -nomx8; write_verilog $(TOP)_synth.v; write_json $(TOP)_synth_final.json" > synth.log

clean:
	rm *.log *.png *.v *.json

implement:
	nextpnr-himbaechel --device=CCGM1A1 --vopt allow-unconstrained --json $(TOP)_synth_final.json -o ccf=pin_constraints.ccf -o out=impl.txt --sdc timing_constraints.sdc --router router2 > routing.log

bitfile:
	gmpack impl.txt impl.bit