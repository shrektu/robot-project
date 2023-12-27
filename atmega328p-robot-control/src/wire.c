#ifndef F_CPU
#define F_CPU       (16000000UL)
#endif

#include "../inc/wire.h"

#include <avr/io.h>
#include <util/delay.h>


/* Helper static functions */

static uint8_t wire_reset(void) {
    uint8_t rc;
    
    DS_DDR |= (1 << DS_DATA_PIN);

    DS_PORT &= ~(1 << DS_DATA_PIN);
    _delay_us(480);

    DS_PORT |= (1 << DS_DATA_PIN);
    _delay_us(70);
    
    DS_DDR &= ~(1 << DS_DATA_PIN);
    rc = (DS_PIN & (1 << DS_DATA_PIN));
    _delay_us(410);

    if (rc == 0) {
        return WIRE_OK;
    } else {
        return WIRE_ERROR;
    }
}

static void wire_write_bit(uint8_t bit) {
    if (bit) {
        DS_DDR |= (1 << DS_DATA_PIN);
        DS_PORT &= ~(1 << DS_DATA_PIN);
        _delay_us(6);
        DS_PORT |= (1 << DS_DATA_PIN);
        _delay_us(64);
    } else {
        DS_DDR |= (1 << DS_DATA_PIN);
        DS_PORT &= ~(1 << DS_DATA_PIN);
        _delay_us(60);
        DS_PORT |= (1 << DS_DATA_PIN);
        _delay_us(10);
    }
}

static uint8_t wire_read_bit(void) {
    uint8_t rc;
    DS_DDR |= (1 << DS_DATA_PIN);
    DS_PORT &= ~(1 << DS_DATA_PIN);
    _delay_us(6);
    DS_PORT |= (1 << DS_DATA_PIN);
    _delay_us(9);
    DS_DDR &= ~(1 << DS_DATA_PIN);
    rc = (DS_PIN & (1 << DS_DATA_PIN));
    _delay_us(55);
    return rc;
}


/* Function definitions from wire.h */

void wire_write(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        wire_write_bit(byte & 0x01);
        byte >>= 1;
    }
}

uint8_t wire_read(void) {
    uint8_t read_byte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        read_byte >>= 1;
        if (wire_read_bit()) {
            read_byte |= 0x80;
        }
    }
    return read_byte;
}


