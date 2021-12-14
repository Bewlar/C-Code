/*
Main memory: 0000 - oxFFEF
GPIO_1: 0xFFF0
GPIO_2: 0xFFF4
Unassigned: 0xFFF8 - 0xFFFF
*/
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t gpo; //unsigned char
    uint8_t gpi; //unsigned char
    uint8_t dir; //unsigned char
} gpio_t, *gpioPtr_t;

gpioPtr_t gpio_1, gpio_2;

uint8_t switches, uint8_t leds;

int main(){
    gpio1_ptr = 0xFFF0;
    gpio2_ptr= 0xFFF4;

    gpio1_ptr->dir = 0xFF;
    gpio2_ptr->dir = 0x00;

    while(1){
    switches = gpio2_ptr->gpi;
    *gpio1_ptr->gpo= switches;
    delay_msecs(500);
    }
}


