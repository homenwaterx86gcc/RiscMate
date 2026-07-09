PREFIX := DesignSources/
DESIGN_SOURCES := $(addprefix $(PREFIX),$(shell cat Misc/compile_files.txt))
PRIMITIVE_SOURCES := $(addprefix $(PREFIX),$(shell cat Misc/primitive_files.txt))
BLACK_BOX_CC_PLL = DesignSources/cc_pll_bb.sv
#INCLUDE_FILES := $(addprefix $(PREFIX),$(shell cat sv_headers.txt))
TOP = top_gatemate
SLANG_PLUGIN = /home/xaver/yosys-slang/build/slang.so
synth:
	yosys -m slang -p "read_slang --std latest --ignore-initial $(DESIGN_SOURCES) DesignSources/cells_sim.v --top $(TOP) -D SYNTHESIS; synth_gatemate -top $(TOP) -luttree -nomx8; write_verilog Synth/$(TOP)_synth.v; write_json Synth/$(TOP)_synth_final.json" > Logs/synth.log

clean:
	rm Logs/*.log *.png Synth/*.v Synth/*.json Impl/*.txt Impl/*.bit

implement:
	nextpnr-himbaechel -l Logs/routing.log --device=CCGM1A1 --vopt allow-unconstrained --json Synth/$(TOP)_synth_final.json -o ccf=Constraints/pin_constraints.ccf -o out=Impl/impl.txt --sdc Constraints/timing_constraints.sdc --router router2 --seed 2

# Same as implement but opens the nextpnr GUI. QT_QPA_PLATFORM=xcb forces XWayland
# (the OSS CAD Suite Qt has no Wayland plugin, so the window won't show otherwise).
gui:
	QT_QPA_PLATFORM=xcb nextpnr-himbaechel --device=CCGM1A1 --vopt allow-unconstrained --json $(TOP)_synth_final.json -o ccf=pin_constraints.ccf --sdc timing_constraints.sdc --router router2 --seed 2 --gui

bitfile:
	gmpack Impl/impl.txt Impl/impl.bit
#Bus 001 Device 017: ID 1209:c0ca Generic Jean THOMAS DirtyJTAG
#flash:
#	sudo ./home/toolchains/oss-cad-suite-linux-x64-20260606/oss-cad-suite/bin/openFPGALoader -c dirtyJtag impl.bit
clk_test:
	yosys -p "read_verilog -sv DesignSources/clkgen_gatemate.sv; synth_gatemate -top clkgen_gatemate -luttree -nomx8; write_verilog clkgen_gatemate_synth.v; write_json clkgen_gatemate_final_synth.json"  

synth_no_slang:
	yosys -p "read_verilog -sv -formal $(DESIGN_SOURCES); synth_gatemate -top $(TOP) -luttree -nomx8; write_verilog $(TOP)_synth.v; write_json $(TOP)_synth_final.json"