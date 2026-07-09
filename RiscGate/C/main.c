#include "demo_system.h"
const char* test_string = "MelixFiller";
int main(void){
    volatile uint32_t* gpio_pointer = (volatile uint32_t*)(0x80000000 + GPIO_OUT_REG);
    *gpio_pointer = 0xFFFFFFFF;
    while(1){
        puts(test_string);
        //run forever
    }
}