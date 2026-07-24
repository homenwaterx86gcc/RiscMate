# Prebuilt reference bitstreams

Both are known-good builds of this design (branch `gatemate-fixes`) verified on
the Olimex GateMateA1-EVB. Flash either one without building anything:

    openFPGALoader -b olimex_gatemateevb prebuilt/blinky_WORKING.bit
    openFPGALoader -b olimex_gatemateevb prebuilt/sos_WORKING.bit

- `blinky_WORKING.bit` - the user LED blinks at roughly 1 s on / 1 s off.
- `sos_WORKING.bit` - the user LED morses SOS (ITU timing, unit ~0.2 s):
  three short, three long, three short, then a ~1.4 s pause, repeating.

Use either to check the board and the programmer are fine before debugging a
build of your own. Note the FPGA configuration is volatile SRAM - after a power
cycle the board reloads from its SPI flash, so re-flash to get this design back.

Built from: ibex_demo_system (bus + ram_2p + timer/GPIO), firmware C/main.c,
10 MHz clock, LED on IO_SB_B6.
