#include <Arduino.h>
#include <main.h>
#include <WiFi.h>

#include <Adafruit_INA219.h>



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
  //Setup I2C
  I2C_A.begin(I2C_A_SDA, I2C_A_SCL, 100000);
  I2C_A.begin(I2C_B_SDA, I2C_B_SCL, 100000);


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

void Scan_Inputs(void *pvParameters) {
  I2C_A_Input_Intensity[0] = I2C_A_INA219_A.getCurrent_mA();
  for(byte i = 0; i < NUMBER_INPUTS_I2C_A; i++) {
    if
  }
  I2C_B_Input_Intensity[0] = I2C_B_INA219_A.getCurrent_mA();
}