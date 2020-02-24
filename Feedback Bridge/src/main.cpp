#include <Arduino.h>
#include <main.h>
#include <WiFi.h>

//use ESP-NOW transmition protocol

void setup() {
  Serial.begin(115200); //only for debbuging purpose
  //Initialize ESP-NOW
  Serial.print(F("Connect To "));
  Serial.print(SSID);
  Serial.print(F("Network"));

  WiFi.begin(SSID, Password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F(""));
  Serial.println(F("Connected !"));
  Serial.print(F("Bridge Current IP Adress :"));
  Serial.println(WiFi.localIP());

  UDP.begin(UDP_Port);
}

void loop() {
  uint8_t 
}

void Transmit() {

}

void Receive() {

}