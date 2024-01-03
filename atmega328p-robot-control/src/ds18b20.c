#ifndef F_CPU
#define F_CPU                   (16000000UL)
#endif


#include <string.h>

#include "../inc/ds18b20.h"
#include "../inc/wire.h"


#define DS18B20_SCRATCHPAD_SIZE (9)

#define DS18B20_READ_ROM        (0x33)
#define DS18B20_MATCH_ROM       (0x55)
#define DS18B20_SKIP_ROM        (0xCC)

#define DS18B20_CONVERT_T       (0x44)
#define DS18B20_READ_SCRATCHPAD (0xBE)


/* Helper static functions */

static uint8_t ds18b20_send_cmd(const uint8_t* rom_code, uint8_t cmd) {
    if (wire_reset() != WIRE_OK) {
        return WIRE_ERROR;
    }

    if (!rom_code) {
        wire_write(DS18B20_SKIP_ROM);
    } else {
        wire_write(DS18B20_MATCH_ROM);
        for (uint8_t i = 0; i < DS18B20_ROM_CODE_SIZE; i++) {
            wire_write(rom_code[i]);
        }
    }

    wire_write(cmd);
    return WIRE_OK;
}

static uint8_t ds18b20_read_scratchpad(const uint8_t* rom_code, uint8_t* scratchpad) {
    if (ds18b20_send_cmd(rom_code, DS18B20_READ_SCRATCHPAD) != WIRE_OK) {
        return WIRE_ERROR;
    }

    for (uint8_t i = 0; i < DS18B20_SCRATCHPAD_SIZE; i++) {
        scratchpad[i] = wire_read();
    }

    uint8_t crc = wire_crc(scratchpad, DS18B20_SCRATCHPAD_SIZE - 1);
    if (scratchpad[DS18B20_SCRATCHPAD_SIZE - 1] == crc) {
        return WIRE_OK;
    } else {
        return WIRE_ERROR;
    }
}


/* Function definitions from ds18b20.h */

uint8_t ds18b20_read_address(uint8_t* rom_code) {
    if (wire_reset() != WIRE_OK) {
        return WIRE_ERROR;
    }

    wire_write(DS18B20_READ_ROM);
    
    for (uint8_t i = 0; i < DS18B20_ROM_CODE_SIZE; i++) {
        rom_code[i] = wire_read();
    } 
    
    uint8_t crc = wire_crc(rom_code, DS18B20_ROM_CODE_SIZE - 1);
    if (rom_code[DS18B20_ROM_CODE_SIZE - 1] == crc) {
        return WIRE_OK;
    } else {
        return WIRE_ERROR;
    }
}

uint8_t ds18b20_start_measure(const uint8_t* rom_code) {
    return ds18b20_send_cmd(rom_code, DS18B20_CONVERT_T);
}

float ds18b20_get_temp(const uint8_t* rom_code) {
    uint8_t scratchpad[DS18B20_SCRATCHPAD_SIZE];
    int16_t temp;

    if (ds18b20_read_scratchpad(rom_code, scratchpad) != WIRE_OK) {
        return 85.0f;
    }
    memcpy(&temp, &scratchpad[0], sizeof(temp));
}
