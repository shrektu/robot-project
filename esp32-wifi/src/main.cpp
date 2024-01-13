#include "uart.hpp"

UART uart;

void setup() {
  Serial.begin(115200); // Initialisation serial communication for debugging 
  uart.begin(9600);     // Initialisation serial communication with PC
}

void loop() {
  const char message[] = "Hello from ESP32!\n";
  uart.sendData(reinterpret_cast<const uint8_t*>(message), sizeof(message) - 1);    // sending data to PC

  uint8_t received_data[50];
  uart.receiveData(received_data, sizeof(received_data));   // receiving data from PC

  Serial.println("Received data from computer: " + String(reinterpret_cast<char*>(received_data)));   // display data from PC

  delay(1000);

}