#include "uart.hpp"

UART::UART() {
    serial = &Serial2;
}

UART::~UART() {

}

void UART::begin(uint32_t baud_rate) {
    serial->begin(baud_rate);
}

void UART::write(uint8_t byte) {
    serial->write(byte);
}
void UART::sendData(const uint8_t* data, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) {
        serial->write(data[i]);
    }
}

void UART::receiveData(uint8_t* buffer, uint32_t buffer_size) {
    uint32_t bytes_read = serial->readBytes(buffer, buffer_size - 1);
    buffer[bytes_read] = '\0';  // Add NULL character at the end of the buffer
}