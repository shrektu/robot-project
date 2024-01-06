#include "../inc/adc.h"

#include <avr/io.h>


/* Function definitions from adc.h */

void ADC_init(void) {
    ADMUX |= (1 << REFS0);
    ADCSRA |= ((1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2)); // presc 128
}

void ADC_start_conversion(void) {
    ADCSRA |= (1 << ADSC);
}
