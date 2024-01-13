#ifndef F_CPU
#define F_CPU           (16000000UL)
#endif

#include <util/delay.h>

#include "../inc/HC-SR04.h"


/* Helper macros */

#define TIMER1_PRESCALER        (8)


/* Static helper functions */

static void timer1_init(void) {
    TCCR1A = 0;            // Normal operation mode
    TCCR1B |= ((1 << ICES1) | (1 << CS11));     // set prescaler to 8, set rising edge as an interrupt trigger 
    TIMSK1 |= (1 << ICIE1);     // Enable interrupt from input capture event pin (ICP1)
}


/* Function definitions from HC-SR04.h file */

void HCSR04_init(void) {
    // configure TRIG pin as an output
    HCSR04_TRIG_DDR |= (1 << HCSR04_TRIG_PIN);

    // configure ECHO pin as an input and pull up to high 
    HCSR04_ECHO_DDR &= ~(1 << HCSR04_ECHO_PIN);
    HCSR04_ECHO_PORT |= (1 << HCSR04_ECHO_PIN);

    // Initialise Timer/Counter 1
    timer1_init();
}

void HCSR04_start_measurement(void) {
    // set TRIG pin for 10us to start measuring
    HCSR04_TRIG_PORT |= (1 << HCSR04_TRIG_PIN);
    _delay_us(10);
    HCSR04_TRIG_PORT &= ~(1 << HCSR04_TRIG_PIN);
}


