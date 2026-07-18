#include "gpio.h"
//Versuche LED zu blinken
#define GPIO_BASE_ADDRESS 0x80000000
// Inner loop iterations per "ms". The volatile counter costs ~10 cycles per
// iteration, so at 10 MHz ~1000 iterations ~= 1 ms. The previous value (100000)
// made one "ms" ~100 ms, i.e. ~100 s per half period - the LED looked dead.
#define CLK_SPEED 1000
int main(void){
    volatile uint32_t* pointer_to_gpio = (volatile uint32_t*)(GPIO_BASE_ADDRESS);
    //Laut gpio.h ist gpio_out bei 0x0
    volatile uint16_t delay_ms = 1000;
    while(1){
        for(volatile uint16_t i = 0; i<delay_ms; i++){
            for(volatile uint32_t j = 0; j<CLK_SPEED; ++j){
                asm volatile("nop");
            }
        }
        *pointer_to_gpio = 1;
        for(volatile uint16_t i = 0; i<delay_ms; i++){
            for(volatile uint32_t j = 0; j<CLK_SPEED; ++j){
                asm volatile("nop");
            }
        }
        *pointer_to_gpio = 0;

}

}