#include "common.hpp"
#include "uart.hpp"

#define STM32WB55xx

#include "stm32wbxx.h"


void uart_init(uint32_t baud) {
    GPIO_TypeDef* gpio = GPIOB;

    /* Enable GPIOB */
    RCC->AHB2ENR |= BIT(1);

    /* Enable USART */
    RCC->APB2ENR |= BIT(14);

    uint32_t af = 7;

    uint32_t tx = 6;
    uint32_t rx = 7;

    gpio->OTYPER |= BIT(rx);
    gpio->OSPEEDR &= ~((3UL << 2 * rx) | (3UL << 2 * tx));
    gpio->OSPEEDR |= (1UL << 2 * rx) | (1UL << 2 * tx);

    gpio->PUPDR &= ~((3UL << 2 * rx) | (3UL << 2 * tx));
    gpio->PUPDR |= (1UL << 2 * rx) | (1UL << 2 * tx);

    gpio->MODER &= ~((3UL << 2 * rx) | (3UL << 2 * tx));
    gpio->MODER |= (2UL << 2 * rx) | (2UL << 2 * tx);

    gpio->AFR[rx / 8] &= ~(15UL << 4 * (rx % 8));
    gpio->AFR[rx / 8] |= af << 4 * (rx % 8);

    gpio->AFR[tx / 8] &= ~(15UL << 4 * (tx % 8));
    gpio->AFR[tx / 8] |= af << 4 * (tx % 8);

    USART1->CR1 = 0;

    USART1->CR1 |= BIT(2) | BIT(3) | BIT(5);

    uint32_t usartdiv = 4000000 / baud;
    USART1->BRR = usartdiv;

    USART1->CR1 |= BIT(0);
}


void uart_transmit_char(char c) {
   USART1->TDR = (uint32_t)c;

    while (!IS_FLAG_SET(USART1->ISR, 7)) {};
}


void uart_transmit(const char* buffer) {
    for (;*buffer != '\0';buffer++) {
        uart_transmit_char(*buffer);
    }
}
