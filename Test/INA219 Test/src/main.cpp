#include <Arduino.h>
#include <Adafruit_INA219.h>

#define I2C_A_SDA 27
#define I2C_A_SCL 26
#define I2C_B_SDA 14
#define I2C_B_SCL 12

TwoWire I2C_A = TwoWire(0); //Channel A
TwoWire I2C_B = TwoWire(1); // Channel B

Adafruit_INA219 I2C_A_INA219(0x40);
Adafruit_INA219 I2C_B_INA219(0x40);

float Calibration = 0;

float Temp;

void setup() {
  //Setup Serial
  Serial.begin(115200);
  Serial.println("Test serial monitor");
  //Setup I2C
  I2C_A.begin(I2C_A_SDA, I2C_A_SCL, 1000000);
  I2C_B.begin(I2C_B_SDA, I2C_B_SCL, 1000000);

  I2C_A_INA219.begin(&I2C_A);
  I2C_B_INA219.begin(&I2C_B);
  //Scan devices on I2C
  Serial.println("Scan I2C Devices On I2C_A :");
  byte Error;
  for(byte i = 0; i < 127; i++)
  {
    I2C_A.beginTransmission(i);
    Error = I2C_A.endTransmission();
    if (Error == 0)
    {
      Serial.print(F("I2C Device Found At Adress 0x"));
      if (i < 16)
      {
        Serial.print("0");
      }
      Serial.println(i, HEX);
    }
    else if (Error == 4) {
      Serial.print(F("Unknow Error At Adress 0x"));
      if (i < 16)
      {
        Serial.print("0");
      }
      Serial.println(i, HEX);
    }
  }
  for(byte i = 0; i < 127; i++)
  {
    I2C_B.beginTransmission(i);
    Error = I2C_B.endTransmission();
    if (Error == 0)
    {
      Serial.print(F("I2C Device Found At Adress 0x"));
      if (i < 16)
      {
        Serial.print("0");
      }
      Serial.println(i, HEX);
    }
    else if (Error == 4) {
      Serial.print(F("Unknow Error At Adress 0x"));
      if (i < 16)
      {
        Serial.print("0");
      }
      Serial.println(i, HEX);
    }
  }
  Serial.print("Calibration :");
  for(int i = 0; i < 500; i++) {
    Temp = I2C_A_INA219.getCurrent_mA();
    if (Temp < 0) {
      Calibration -= Temp;
    }
    else {
      Calibration += Temp;
    }
    
  }
  Calibration /= 500;
  Serial.println(Calibration);
}

void loop() {
  Serial.print("INA219_A Intensity :");
  float Current = 0;
  for(int i = 0; i < 500; i++) {
    Temp = I2C_A_INA219.getCurrent_mA();
    if (Temp < 0) {
      Current -= Temp;
    }
    else {
      Current += Temp;
    }
    
  }
  Current /= 500;
  Current -= Calibration;
  Serial.println(Current);
}