all: led_test.bit

synth:
	yosys -p "read_verilog -sv led_high.sv; synth_gatemate -top ledhigh -luttree -nomx8; write_json ledhigh_netlist0.json"

implement:
	nextpnr-himbaechel --device=CCGM1A1 --json ledhigh_netlist0.json -o ccf=pins.ccf -o out=led_test.txt --router router2

bitfile:
	gmpack led_test.txt led_test.bit

clean:
	rm -f *.json *.txt *.bit