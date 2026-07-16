#include "demo_system.h"

// Olimex GateMateA1-EVB: single active-low user LED on gp_o[0].
// Blink it (toggle) as visible proof the core is running, and print over UART.

static void delay(void) {
    for (volatile uint32_t i = 0; i < 500000u; i++) {
    }
}

int main(void) {
    volatile uint32_t *gpio_out = (volatile uint32_t *)(GPIO_BASE + GPIO_OUT_REG);
    uint32_t led = 0;
    while (1) {
        *gpio_out = led;      // active-low LED: 0 = lit, 1 = dark
        puts("MelixFiller");  // also emit on UART each toggle
        led ^= 1u;
        delay();
    }
}
