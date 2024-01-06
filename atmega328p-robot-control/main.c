#ifndef F_CPU  
#define F_CPU   (16000000UL)
#endif

#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#include "inc/motors.h"
#include "inc/lcd.h"
#include "inc/adc.h"


volatile uint16_t adc_value;

void init_timer(void);  // Initialise timer1 to count for 50ms


int main(void) {
    adc_value = 0;

    DRV8835_init();
    PWM_init();
//   ADC_init();
    lcd_init();
    PWM_set_duty_cycle(adc_value);
    init_timer();
    
    while(1) {
 
   }

    return EXIT_SUCCESS;
}


void init_timer(void) {
    TCCR1B |= (1 << WGM12); // CTC mode
    TCCR1B |= ((1 << CS10) | (1 << CS12));  // Prescaler = 1024
    OCR1A = 781;    // Compare match value for 50ms
    TIMSK1 |= (1 << OCIE1A);    // Enable interrupt for compare output channel A
}


ISR(TIMER1_COMPA_vect) {
    adc_value += 1;   
}
