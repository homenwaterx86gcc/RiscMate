#include "gpio.h"
//Versuche LED zu blinken
#define GPIO_BASE_ADDRESS 0x80000000
#define CLK_SPEED 100000
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