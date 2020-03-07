#include <Arduino.h>
#include <main.h>
#include <WiFi.h>

WiFiUDP UDP;

//use ESP-NOW transmition protocol

void setup() {
  //Setup Debug Communication
  Serial.begin(115200);
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
  xTaskCreatePinnedToCore(Scan_Slave, "Scan_Slave", 4096, NULL, 2, &Scan_Slave_Handle, 0);
}

void loop() {
  vTaskDelete(NULL);
}

void Scan_Slave(void *pvParameters) {
  (void) pvParameters;
  for(;;) {
    uint8_t Buffer[10] = {0, 0, 0, 0, 0};
    Serial.println(F("Start Scanning All Slave ..."));
    for(byte i = 0; i < NUMBER_SLAVE; i++) {
      UDP.beginPacket(Slave_IP_Adress[i], UDP_PORT);
      UDP.write('S');
      UDP.endPacket();
      UDP.parsePacket();
      byte ii = 0;
      while(UDP.read(Buffer, 5) == 0 && ii < 50) { //wait 5000 ms slave reply - check every 100 ms
        Serial.println(F("Waiting For Slave ..."));
        vTaskDelay(pdMS_TO_TICKS(100));
        ii++;
      }
      if(ii > 50) { //if slave doesn't reply, its ways will be protected (occupy)
        Serial.print(F("Slave "));
        Serial.print(i);
        Serial.println(F("Timed Out !"));
        Serial.println(F("Protect Slave's Railways !"));
        Buffer[1] = 255;
        Buffer[2] = 255;
      }
      else { //update local register with the buffer
        for(byte iii = 0; iii < 8; iii++) {
          bitWrite(Slave_Input_Register[i], iii, bitRead(Buffer[0], iii));
        }
        for(byte iii = 8; iii < 16; iii++) {
          bitWrite(Slave_Input_Register[i], iii, bitRead(Buffer[1], iii));
        }
      }
      vTaskDelay(10);
    }
  }
}

void S88_PS() {
  S88_Selected_Slave = 0;
  S88_Selected_Input = 0;
}

void S88_Clock() { //transmition clock for each bit
  digitalWrite(S88_Data_Out_Pin, bitRead(Slave_Input_Register[S88_Selected_Slave], S88_Selected_Input));
  S88_Selected_Input++;
  if(S88_Selected_Input > 15) {
    S88_Selected_Input = 0;
    S88_Selected_Slave++;
  }
}