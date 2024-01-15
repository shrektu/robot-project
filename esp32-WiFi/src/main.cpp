#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HardwareSerial.h>

#include "webpage.hpp"


/* General macro definitions */

#define SERIAL_BAUD   (115200)
#define UART_BAUD     (9600)

#define RX_PIN        (16)
#define TX_PIN        (17)


/* Typedef enumeration for instructions sent to the atmega328p */

typedef enum {
  STOP,
  GO_FORWARD,
  GO_BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
  LCD_SWITCH_VIEW
}ATMEGA_COMMANDS_t;


/* SSID and password for ESP32 Access Point*/

const char* ssid = "Transmitator";
const char* password = "transmitancja123";


/* Instances of AsyncWebServer and AsyncWebSocket classes */

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");


/* Instance of UART class*/

HardwareSerial UART(2);


/* This function handles connection with the root page*/

void handleRoot(AsyncWebServerRequest *request) 
{
  request->send_P(200, "text/html", htmlHomePage);
}


/* This function handles "Page not Found" error */

void handleNotFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "File Not Found");
}


/* This function handling a WebSocket event */

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      AwsFrameInfo *info;
      info = (AwsFrameInfo *)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        uint8_t value = *data;
        Serial.printf("Received value from WebSocket: %u\n", value);
        UART.write(value); 
      }
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;
  }
}


void setup(void) {
  Serial.begin(SERIAL_BAUD);
  UART.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
  
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  ws.cleanupClients();
}