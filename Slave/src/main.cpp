#include <Arduino.h>
#include <main.h>
#include <WiFi.h>

WiFiUDP UDP;

void setup() {
  /Serial.begin(115200);
  //Setup Network
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
  UDP.begin(UDP_PORT);
  //Setup S88
  pinMode(S88_Clock_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(S88_Clock_Pin), S88_Clock, RISING);
  pinMode(S88_PS_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(S88_PS_Pin), S88_PS, RISING);
  pinMode(S88_Data_Out_Pin, OUTPUT);
  //Task
  xTaskCreatePinnedToCore(Scan_Gateway, "Scan_Gateway", 4096, NULL, 2, &Scan_Gateway_Handle, 0);
}

void loop() {
  vTaskDelete(NULL);
}

void Scan_Gateway(void *pvParameters) {
  (void) pvParameters;
  for(;;) {
    uint8_t Buffer[5] = {0, 0, 0, 0, 0};
    Serial.println(F("Start Scanning Gateway ..."));
    while(UDP.read(Buffer, 5) == 0) {
      vTaskDelay(pdMS_TO_TICK(100));
    }
    switch(Buffer[1]) {
      case 'G':
        
      default:
        Serial.println(F("Unknow command"));
        break;
    }
  }
}