#ifndef F_CPU
#define F_CPU		(16000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../inc/usart.h"


#define BAUD		(9600)
#define UBRRVAL     ((F_CPU/(BAUD*16UL))-1)


/* Function definitions from usart.h */

void USART_init(void) {
	UBRR0L = UBRRVAL;
	UBRR0H = UBRRVAL >> 8;

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Enable RX, TX, and RX complete interrupt
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
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
