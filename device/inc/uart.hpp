
#ifndef UART_HPP
#define UART_HPP

#include <cstdint>

void uart_init(uint32_t baud);
void uart_transmit(const char* buffer);

#endif
