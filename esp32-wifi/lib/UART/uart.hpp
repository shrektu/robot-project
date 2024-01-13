#pragma once

#include <Arduino.h>
#include <stdint.h>


class UART {
    public:
        UART();
        ~UART();

        void begin(uint32_t baud_rate);
        void sendData(const uint8_t* data, uint32_t length);
        void receiveData(uint8_t* buffer, uint32_t buffer_size);

    private:
        HardwareSerial* serial;
};
