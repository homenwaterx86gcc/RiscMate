// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

// This is the top level SystemVerilog file that connects the IO on the board to the Ibex Demo System.
//Wir lassen das alles erstmal auf 25MHz laufen, was auch die Clock von Olimex Board ist
module top_gatemate #(
  parameter SRAMInitFile = "firmware_mem_init.svh"
) (
  // These inputs are defined in data/pins_artya7.xdc
  // In unserem Falle in pin_constraints.ccf 
  input         IO_CLK,
  input         IO_RST_N,
  input  [ 1:0] SW,
  //input  [ 3:0] BTN, entfernt weil wir fürst erste keinen button brauchen
  output [ 1:0] LED
  //PWM signal kommt weg
  //output [3:0] RGB_LED, //Davor output[11:0] reduziert
  //output [ 3:0] DISP_CTRL, brauchen wir auch nicht
 // input         UART_RX,
 // output        UART_TX
 // input         SPI_RX, benutzen wir garnicht mehr
  //output        SPI_TX,
 // output        SPI_SCK
);
  logic clk_sys, rst_sys_n;
  // The board has no reset button and IO_RST_N is not wired to a pad, so it
  // would float. Generate reset internally: hold low for 128 clocks after
  // configuration, then release and saturate.
  logic [7:0] por_cnt = 8'd0;
  always @(posedge clk_sys) begin
    if (!por_cnt[7]) por_cnt <= por_cnt + 8'd1;
  end
  assign rst_sys_n = por_cnt[7];
  wire _unused_rst = IO_RST_N;
  // Instantiating the Ibex Demo System.
  ibex_demo_system #(
    .GpiWidth     ( 1            ), //Davor 8 wegen routing reduziert
    .GpoWidth     ( 1            ), //Davor 8 wegen routing reduziert
    //.PwmWidth     ( 4           ), //Davor 12 wegen routing reduziert Wir benutzen den PWM aber garnicht
    .SRAMInitFile ( SRAMInitFile )
  ) u_ibex_demo_system (
    //input
    //Hier reichen wir direkt IO_CLK und IO_RST_N durch anstatt clk_sys und rst_sys_n
    .clk_sys_i (clk_sys),
    .rst_sys_ni(rst_sys_n),
    .gp_i      (SW), //Hier gabs davor noch den Button
    .uart_rx_i (1'b1),   // idle high - port must be driven

    //output
    .gp_o     (LED), //hier gabs davor DISP_CTRL
    //PWM benutzen wir nicht mehr
    //.pwm_o    (RGB_LED),
    //.uart_tx_o(UART_TX),

    .spi_rx_i  (1'b0),   // unused, but must be driven
    //.spi_tx_o (SPI_TX),
    //.spi_sck_o(SPI_SCK),

    .trst_ni(1'b1),
    .tms_i  (1'b0),
    .tck_i  (1'b0),
    .td_i   (1'b0),
    .td_o   ()
  );

  //hier ein input-buffer für die clock
  // Clock input: drive clk_sys straight from the pad. The pad buffer is
  // configured by the CCF (Pin_in ... | SCHMITT_TRIGGER=true) and nextpnr
  // promotes this net to the global clock network.
  // NOTE: the previous hand-instantiated CC_IBUF forced V_IO("1.8") and
  // SCHMITT_TRIGGER(0), which is the wrong I/O standard for this board's
  // oscillator - the clock did not reach the fabric reliably.
  assign clk_sys = IO_CLK;

/*
Vielleicht input buffern wir später auch den reset
  CC_IBUF #(
  .PIN_NAME("IO_SB_A0"),
  .V_IO("1.8"),
  .PULLUP(0),
  .PULLDOWN(0),
  .KEEPER(0),
  .SCHMITT_TRIGGER(0),
  .DELAY_IBF(4'd0),
  .FF_IBF(1'b0)
  ) ibuf_inst_rst (
  .I(IO_RST_N),
  .Y(rst_sys_n)
);
*/

  // Generating the system clock and reset for the FPGA.
  //TODO:Primitve von GateMate einfügen für PLL (funktioniert noch nicht)
  /*
  clkgen_gatemate clkgen(
    .IO_CLK,
    .IO_RST_N,
    .clk_sys,
    .rst_sys_n
  );
*/
endmodule
