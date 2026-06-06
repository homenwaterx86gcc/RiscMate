
//hier erstmal noch garnichts
module clkgen_gatemate (
    input  logic IO_CLK,
    input  logic IO_RST_N,
    output logic clk_sys,
    output logic rst_sys_n
);

    assign clk_sys   = IO_CLK;
    assign rst_sys_n = IO_RST_N;

endmodule