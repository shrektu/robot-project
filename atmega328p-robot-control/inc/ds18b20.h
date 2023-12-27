#pragma once 

/* General macro definitions */

#define DS18B20_PORT        (PORTD)
#define DS18B20_DDR         (DDRD)
#define DS18B20_PIN         (PIND)
#define DS18B20_DATA_PIN    (PD2)


/* Function prototypes */

/* This function reads the temperature from the sensor and returns the result in Celsius degrees */
float ds18b20_read_temp(void);

