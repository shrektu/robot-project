#pragma once 

#include <avr/io.h>

/* General macro definitions */

#define HCSR04_TRIG_PORT        (PORTB)
#define HCSR04_TRIG_DDR         (DDRB)
#define HCSR04_TRIG_PIN         (PINB3)

#define HCSR04_ECHO_PORT        (PORTB)
#define HCSR04_ECHO_DDR         (DDRB)
#define HCSR04_ECHO_PIN         (PINB0)

/* Function prototypes */

// This function initialises HC-SR04 sensor
void HCSR04_init(void);

// This function returns pulse duration in ms
void HCSR04_start_measurement(void);
