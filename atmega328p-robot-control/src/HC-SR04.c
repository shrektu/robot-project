#ifndef F_CPU
#define F_CPU           (16000000UL)
#endif

#include <util/delay.h>

#include "../inc/HC-SR04.h"


/* Helper macros */

#define TIMER1_PRESCALER        (8)


/* Volatile global variables */

volatile uint16_t startTime = 0;
volatile uint16_t endTime = 0;
volatile uint8_t measureComplete = 0;   // This flag is set when the measurement is completed
                                

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

    // configure ECHO pin as an input 
    HCSR04_ECHO_DDR &= ~(1 << HCSR04_ECHO_PIN);

    // Initialise Timer/Counter 1
    timer1_init();
}

uint16_t HCSR04_get_pulse_duration(void) {
    // set TRIG pin for 10us to start measuring
    HCSR04_TRIG_PORT |= (1 << HCSR04_TRIG_PIN);
    _delay_us(10);
    HCSR04_TRIG_PORT &= ~(1 << HCSR04_TRIG_PIN);
    
    while (!measureComplete);

    uint16_t pulseDuration = endTime - startTime;
    
    return (uint32_t)pulseDuration * 1000 / (TIMER1_PRESCALER * F_CPU);
}


