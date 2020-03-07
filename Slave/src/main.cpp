#include <Arduino.h>
#include <main.h>
#include <WiFi.h>
#include <Adafruit_INA219.h>

void setup ()
{
  //Set serial for debbug
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
  Serial.print(F("Slave Current IP Adress :"));
  Serial.println(WiFi.localIP());
  UDP.begin(UDP_PORT);
  //Setup I2C
  I2C_A.begin(I2C_A_SDA, I2C_A_SCL, 100000);
  I2C_A.begin(I2C_B_SDA, I2C_B_SCL, 100000);
  //Set Task
  xTaskCreatePinnedToCore(Scan_Gateway, "Scan_Gateway", 4096, NULL, 2, &Scan_Gateway_Handle, 0);
  xTaskCreatePinnedToCore(Scan_Inputs, "Scan_Inputs", 4096, NULL, 2, &Scan_Inputs_Handle, 0);
}

void loop ()
{
  vTaskDelete(NULL);
}

void Scan_Gateway (void *pvParameters)
{
  (void) pvParameters;
  for(;;)
  {
    uint8_t Buffer[5] = {0, 0, 0, 0, 0};
    Serial.println(F("Start Scanning Gateway ..."));
    while(UDP.read(Buffer, 5) == 0)
    {
      vTaskDelay(pdMS_TO_TICKS(100));
    }
    switch (Buffer[1]) 
    {
      case 'S':
        UDP.beginPacket(Gateway_IP_Adress, UDP_PORT);
        UDP.write('A');
        UDP.write(NUMBER_INPUTS_I2C_A);
        UDP.write(I2C_A_Inputs_State[0]);
        UDP.write(I2C_A_Inputs_State[1]);
        UDP.write('B');
        UDP.write(NUMBER_INPUTS_I2C_B);
        UDP.write(I2C_B_Inputs_State[0]);
        UDP.write(I2C_B_Inputs_State[1]);
        UDP.endPacket();
        UDP.parsePacket();
        break;
      default:
        Serial.println(F("Unknow command"));
        break;
    }
    vTaskDelay(10);
  }
}

void Scan_Inputs (void *pvParameters)
{
  (void) pvParameters;
  for(;;)
  {
    //Get Intensity
    I2C_A_Inputs_Intensity[0] = I2C_A_INA219_A.getCurrent_mA();
    I2C_A_Inputs_Intensity[1] = I2C_A_INA219_B.getCurrent_mA();
    I2C_A_Inputs_Intensity[2] = I2C_A_INA219_C.getCurrent_mA();
    I2C_A_Inputs_Intensity[3] = I2C_A_INA219_D.getCurrent_mA();
    I2C_A_Inputs_Intensity[4] = I2C_A_INA219_E.getCurrent_mA();
    I2C_A_Inputs_Intensity[5] = I2C_A_INA219_F.getCurrent_mA();
    I2C_A_Inputs_Intensity[6] = I2C_A_INA219_G.getCurrent_mA();
    I2C_A_Inputs_Intensity[7] = I2C_A_INA219_H.getCurrent_mA();
    I2C_A_Inputs_Intensity[8] = I2C_A_INA219_I.getCurrent_mA();
    I2C_A_Inputs_Intensity[9] = I2C_A_INA219_J.getCurrent_mA();
    I2C_A_Inputs_Intensity[10] = I2C_A_INA219_K.getCurrent_mA();
    I2C_A_Inputs_Intensity[11] = I2C_A_INA219_L.getCurrent_mA();
    I2C_A_Inputs_Intensity[12] = I2C_A_INA219_M.getCurrent_mA();
    I2C_A_Inputs_Intensity[13] = I2C_A_INA219_N.getCurrent_mA();
    I2C_A_Inputs_Intensity[14] = I2C_A_INA219_O.getCurrent_mA();
    I2C_A_Inputs_Intensity[15] = I2C_A_INA219_P.getCurrent_mA();

    I2C_B_Inputs_Intensity[0] = I2C_B_INA219_A.getCurrent_mA();
    I2C_B_Inputs_Intensity[1] = I2C_B_INA219_B.getCurrent_mA();
    I2C_B_Inputs_Intensity[2] = I2C_B_INA219_C.getCurrent_mA();
    I2C_B_Inputs_Intensity[3] = I2C_B_INA219_D.getCurrent_mA();
    I2C_B_Inputs_Intensity[4] = I2C_B_INA219_E.getCurrent_mA();
    I2C_B_Inputs_Intensity[5] = I2C_B_INA219_F.getCurrent_mA();
    I2C_B_Inputs_Intensity[6] = I2C_B_INA219_G.getCurrent_mA();
    I2C_B_Inputs_Intensity[7] = I2C_B_INA219_H.getCurrent_mA();
    I2C_B_Inputs_Intensity[8] = I2C_B_INA219_I.getCurrent_mA();
    I2C_B_Inputs_Intensity[9] = I2C_B_INA219_J.getCurrent_mA();
    I2C_B_Inputs_Intensity[10] = I2C_B_INA219_K.getCurrent_mA();
    I2C_B_Inputs_Intensity[11] = I2C_B_INA219_L.getCurrent_mA();
    I2C_B_Inputs_Intensity[12] = I2C_B_INA219_M.getCurrent_mA();
    I2C_B_Inputs_Intensity[13] = I2C_B_INA219_N.getCurrent_mA();
    I2C_B_Inputs_Intensity[14] = I2C_B_INA219_O.getCurrent_mA();
    I2C_B_Inputs_Intensity[15] = I2C_B_INA219_P.getCurrent_mA();
    //Set Byte
    for (byte i = 0; i < NUMBER_INPUTS_I2C_A; i++) 
    {
      if (i > 7)
      {
        if (I2C_A_Inputs_Intensity[i] >= INTENSITY_TRIGGER_VALUE)
        {
          bitSet(I2C_A_Inputs_State[1], i-8);
        }
        else {
          bitClear(I2C_A_Inputs_State[1], i-8);
        }
      }
      else {
        if (I2C_A_Inputs_Intensity[i] >= INTENSITY_TRIGGER_VALUE)
        {
          bitSet(I2C_A_Inputs_State[0], i);
        }
        else {
          bitClear(I2C_A_Inputs_State[0], i);
        }
      }
    }
    for (byte i = 0; i < NUMBER_INPUTS_I2C_A; i++) 
    {
      if (i > 7)
      {
        if (I2C_B_Inputs_Intensity[i] >= INTENSITY_TRIGGER_VALUE)
        {
          bitSet(I2C_B_Inputs_State[1], i-8);
        }
        else {
          bitClear(I2C_B_Inputs_State[1], i-8);
        }
      }
      else {
        if (I2C_B_Inputs_Intensity[i] >= INTENSITY_TRIGGER_VALUE)
        {
          bitSet(I2C_B_Inputs_State[0], i);
        }
        else {
          bitClear(I2C_B_Inputs_State[0], i);
        }
      }
    }
    //Get Bus Voltage (only for debuging purpose)
    I2C_A_Inputs_Tension[0] = I2C_A_INA219_A.getBusVoltage_V();
    I2C_A_Inputs_Tension[1] = I2C_A_INA219_B.getBusVoltage_V();
    I2C_A_Inputs_Tension[2] = I2C_A_INA219_C.getBusVoltage_V();
    I2C_A_Inputs_Tension[3] = I2C_A_INA219_D.getBusVoltage_V();
    I2C_A_Inputs_Tension[4] = I2C_A_INA219_E.getBusVoltage_V();
    I2C_A_Inputs_Tension[5] = I2C_A_INA219_F.getBusVoltage_V();
    I2C_A_Inputs_Tension[6] = I2C_A_INA219_G.getBusVoltage_V();
    I2C_A_Inputs_Tension[7] = I2C_A_INA219_H.getBusVoltage_V();
    I2C_A_Inputs_Tension[8] = I2C_A_INA219_I.getBusVoltage_V();
    I2C_A_Inputs_Tension[9] = I2C_A_INA219_J.getBusVoltage_V();
    I2C_A_Inputs_Tension[10] = I2C_A_INA219_K.getBusVoltage_V();
    I2C_A_Inputs_Tension[11] = I2C_A_INA219_L.getBusVoltage_V();
    I2C_A_Inputs_Tension[12] = I2C_A_INA219_M.getBusVoltage_V();
    I2C_A_Inputs_Tension[13] = I2C_A_INA219_N.getBusVoltage_V();
    I2C_A_Inputs_Tension[14] = I2C_A_INA219_O.getBusVoltage_V();
    I2C_A_Inputs_Tension[15] = I2C_A_INA219_P.getBusVoltage_V();
    
    I2C_B_Inputs_Tension[0] = I2C_B_INA219_A.getBusVoltage_V();
    I2C_B_Inputs_Tension[1] = I2C_B_INA219_B.getBusVoltage_V();
    I2C_B_Inputs_Tension[2] = I2C_B_INA219_C.getBusVoltage_V();
    I2C_B_Inputs_Tension[3] = I2C_B_INA219_D.getBusVoltage_V();
    I2C_B_Inputs_Tension[4] = I2C_B_INA219_E.getBusVoltage_V();
    I2C_B_Inputs_Tension[5] = I2C_B_INA219_F.getBusVoltage_V();
    I2C_B_Inputs_Tension[6] = I2C_B_INA219_G.getBusVoltage_V();
    I2C_B_Inputs_Tension[7] = I2C_B_INA219_H.getBusVoltage_V();
    I2C_B_Inputs_Tension[8] = I2C_B_INA219_I.getBusVoltage_V();
    I2C_B_Inputs_Tension[9] = I2C_B_INA219_J.getBusVoltage_V();
    I2C_B_Inputs_Tension[10] = I2C_B_INA219_K.getBusVoltage_V();
    I2C_B_Inputs_Tension[11] = I2C_B_INA219_L.getBusVoltage_V();
    I2C_B_Inputs_Tension[12] = I2C_B_INA219_M.getBusVoltage_V();
    I2C_B_Inputs_Tension[13] = I2C_B_INA219_N.getBusVoltage_V();
    I2C_B_Inputs_Tension[14] = I2C_B_INA219_O.getBusVoltage_V();
    I2C_B_Inputs_Tension[15] = I2C_B_INA219_P.getBusVoltage_V();
    //Get Power Consuption (only for debuging purpose)
    I2C_A_Inputs_Power[0] = I2C_A_INA219_A.getPower_mW();
    I2C_A_Inputs_Power[1] = I2C_A_INA219_B.getPower_mW();
    I2C_A_Inputs_Power[2] = I2C_A_INA219_C.getPower_mW();
    I2C_A_Inputs_Power[3] = I2C_A_INA219_D.getPower_mW();
    I2C_A_Inputs_Power[4] = I2C_A_INA219_E.getPower_mW();
    I2C_A_Inputs_Power[5] = I2C_A_INA219_F.getPower_mW();
    I2C_A_Inputs_Power[6] = I2C_A_INA219_G.getPower_mW();
    I2C_A_Inputs_Power[7] = I2C_A_INA219_H.getPower_mW();
    I2C_A_Inputs_Power[8] = I2C_A_INA219_I.getPower_mW();
    I2C_A_Inputs_Power[9] = I2C_A_INA219_J.getPower_mW();
    I2C_A_Inputs_Power[10] = I2C_A_INA219_K.getPower_mW();
    I2C_A_Inputs_Power[11] = I2C_A_INA219_L.getPower_mW();
    I2C_A_Inputs_Power[12] = I2C_A_INA219_M.getPower_mW();
    I2C_A_Inputs_Power[13] = I2C_A_INA219_N.getPower_mW();
    I2C_A_Inputs_Power[14] = I2C_A_INA219_O.getPower_mW();
    I2C_A_Inputs_Power[15] = I2C_A_INA219_P.getPower_mW();
    
    I2C_B_Inputs_Power[0] = I2C_B_INA219_A.getPower_mW();
    I2C_B_Inputs_Power[1] = I2C_B_INA219_B.getPower_mW();
    I2C_B_Inputs_Power[2] = I2C_B_INA219_C.getPower_mW();
    I2C_B_Inputs_Power[3] = I2C_B_INA219_D.getPower_mW();
    I2C_B_Inputs_Power[4] = I2C_B_INA219_E.getPower_mW();
    I2C_B_Inputs_Power[5] = I2C_B_INA219_F.getPower_mW();
    I2C_B_Inputs_Power[6] = I2C_B_INA219_G.getPower_mW();
    I2C_B_Inputs_Power[7] = I2C_B_INA219_H.getPower_mW();
    I2C_B_Inputs_Power[8] = I2C_B_INA219_I.getPower_mW();
    I2C_B_Inputs_Power[9] = I2C_B_INA219_J.getPower_mW();
    I2C_B_Inputs_Power[10] = I2C_B_INA219_K.getPower_mW();
    I2C_B_Inputs_Power[11] = I2C_B_INA219_L.getPower_mW();
    I2C_B_Inputs_Power[12] = I2C_B_INA219_M.getPower_mW();
    I2C_B_Inputs_Power[13] = I2C_B_INA219_N.getPower_mW();
    I2C_B_Inputs_Power[14] = I2C_B_INA219_O.getPower_mW();
    I2C_B_Inputs_Power[15] = I2C_B_INA219_P.getPower_mW();
  }
}