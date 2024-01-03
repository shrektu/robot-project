#pragma once 

#include <stdint.h>


/* General macro definitions */

#define DS18B20_PORT            (PORTD)
#define DS18B20_DDR             (DDRD)
#define DS18B20_PIN             (PIND)
#define DS18B20_DATA_PIN        (PD2)

#define DS18B20_ROM_CODE_SIZE   (8)


/* Function prototypes */

/* This function reads sensor address and calculates CRC */
uint8_t ds18b20_read_address(uint8_t* rom_code);

/* This function starts temperature measurement */
uint8_t ds18b20_start_measure(const uint8_t* rom_code);

/* This function returns temperature value in Celsius degree */
float ds18b20_get_temp(const uint8_t* rom_code);
