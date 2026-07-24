#include "gpio.h"

// Morse "SOS" on the single LED using proper ITU timing.
//   dot = 1 unit, dash = 3 units, gap in letter = 1, between letters = 3,
//   between words = 7. UNIT ~0.2 s (about 6 WPM) - easy to read by eye.
//
// LED only: this SoC has no UART on the bus yet (wiring it up is the next
// task). Walks the pattern from a string in .rodata, so it still exercises
// instruction fetch, data-memory reads, function calls and MMIO writes.
// No multiply or divide (this core is built with RV32M = RV32MNone).

#define GPIO_BASE_ADDRESS 0x80000000
// Inner-loop iterations per "ms": the volatile counter costs ~10 cycles per
// iteration, so at 10 MHz ~1000 iterations ~= 1 ms.
#define CLK_SPEED 1000
#define UNIT_MS   200            // one morse time unit

static volatile uint32_t *const gpio =
    (volatile uint32_t *)GPIO_BASE_ADDRESS;   // gpio_out is at offset 0

static void delay_ms(uint16_t ms) {
    for (volatile uint16_t i = 0; i < ms; i++)
        for (volatile uint32_t j = 0; j < CLK_SPEED; ++j)
            asm volatile("nop");
}
static void led_on(void)  { *gpio = 0u; }     // active low: 0 = lit
static void led_off(void) { *gpio = 1u; }

int main(void) {
    static const char msg[] = "... --- ...";  // '.' dot, '-' dash, ' ' letter gap

    while (1) {
        for (const char *p = msg; *p != '\0'; p++) {
            if (*p == ' ') {
                delay_ms(2 * UNIT_MS);         // +2 => 3 units between letters
            } else {
                led_on();
                delay_ms((*p == '-') ? 3 * UNIT_MS : UNIT_MS);
                led_off();
                delay_ms(UNIT_MS);             // 1 unit between elements
            }
        }
        delay_ms(6 * UNIT_MS);                 // +1 already emitted => 7 units
    }
}
