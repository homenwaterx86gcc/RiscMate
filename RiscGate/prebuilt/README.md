# Prebuilt reference bitstream

`blinky_WORKING.bit` is a known-good build of this design (branch
`gatemate-fixes`) verified on the Olimex GateMateA1-EVB.

Flash it without building anything:

    openFPGALoader -b olimex_gatemateevb prebuilt/blinky_WORKING.bit

Expected: the user LED blinks at roughly 1 s on / 1 s off.

Use it to check the board and the programmer are fine before debugging a build
of your own. Note the FPGA configuration is volatile SRAM - after a power cycle
the board reloads from its SPI flash, so re-flash to get this design back.

Built from: ibex_demo_system (bus + ram_2p + timer/GPIO), firmware C/main.c,
10 MHz clock, LED on IO_SB_B6.
