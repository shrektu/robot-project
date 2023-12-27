#pragma once

#include <avr/io.h>


/* General helper macro definitions */

#define WIRE_OK         (0)
#define WIRE_ERROR      (1)

#define DS_PORT         (PORTB)
#define DS_DDR          (DDRB)
#define DS_PIN          (PINB)
#define DS_DATA_PIN     (PB2)


/* Function prototypes */

/* This function sends a byte of data via 1-wire interface */
void wire_write(uint8_t byte);

/* This function reads a byte of data from 1-wire interface */
uint8_t wire_read(void);
