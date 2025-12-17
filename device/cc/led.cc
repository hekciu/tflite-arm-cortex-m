#include <cstdbool>

#define STM32WB55xx
#include "stm32wbxx.h"

#include "common.hpp"
#include "led.hpp"


static bool led_on = false;


void setup_green_led(void) {
    RCC->AHB2ENR |= BIT(1);

    GPIOB->MODER &= ~(3UL << 2 * 0);
    GPIOB->MODER |= 1UL << 2 * 0;
}


void blink_green_led(void) {
    if (led_on) {
        led_on = false;

        GPIOB->BSRR &= ~BIT(0);
        GPIOB->BSRR |= BIT(16);
    } else {
        led_on = true;

        GPIOB->BSRR &= ~BIT(16);
        GPIOB->BSRR |= BIT(0);
    }
}
