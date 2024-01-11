#pragma once

/* Function prototypes */

// This function initialises USART
void USART_init(void);

// This function transmits a byte of data
void USART_transmit(uint8_t data);

// This functions receives a byte of data
uint8_t USART_receive(void);