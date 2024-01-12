#ifndef F_CPU
#define F_CPU		(16000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../inc/usart.h"


#define BAUD		(9600)
#define UBBR		((F_CPU) / (16) / ((BAUD) - (1)))


/* Function definitions from usart.h */

void USART_init(void) {
	UBRR0L = (uint8_t)UBBR;
	UBRR0H = (uint8_t)(UBBR >> 8);

	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
}

void USART_transmit(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

uint8_t USART_receive(void) {
    if (UCSR0A & (1 << RXC0)) {
        return UDR0;
    } else {
        return 0xFF;	// return 0xFF if there is no data to receive
    }
}
