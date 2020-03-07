#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <Arduino.h>
#include <main.h>
#include <WiFi.h>
#include <Adafruit_INA219.h>
//Parameters for different configuration
#define UDP_PORT 8888
#define I2C_A_SDA 27
#define I2C_A_SCL 26
#define I2C_B_SDA 33
#define I2C_B_SCL 32
#define NUMBER_INPUTS_I2C_A 1
#define NUMBER_INPUTS_I2C_B 1
#define INTENSITY_TRIGGER_VALUE 5.0
//Declare UDP
WiFiUDP UDP;
//Declare each I2C Channel that will be used
TwoWire I2C_A = TwoWire(0);
TwoWire I2C_B = TwoWire(1);
//I2C A
Adafruit_INA219 I2C_A_INA219_A(0x40);
Adafruit_INA219 I2C_A_INA219_B(0x41);
Adafruit_INA219 I2C_A_INA219_C(0x42);
Adafruit_INA219 I2C_A_INA219_D(0x43);
Adafruit_INA219 I2C_A_INA219_E(0x44);
Adafruit_INA219 I2C_A_INA219_F(0x45);
Adafruit_INA219 I2C_A_INA219_G(0x46);
Adafruit_INA219 I2C_A_INA219_H(0x47);
Adafruit_INA219 I2C_A_INA219_I(0x48);
Adafruit_INA219 I2C_A_INA219_J(0x49);
Adafruit_INA219 I2C_A_INA219_K(0x4A);
Adafruit_INA219 I2C_A_INA219_L(0x4B);
Adafruit_INA219 I2C_A_INA219_M(0x4C);
Adafruit_INA219 I2C_A_INA219_N(0x4D);
Adafruit_INA219 I2C_A_INA219_O(0x4E);
Adafruit_INA219 I2C_A_INA219_P(0x4F);
//I2C B
Adafruit_INA219 I2C_B_INA219_A(0x40);
Adafruit_INA219 I2C_B_INA219_B(0x41);
Adafruit_INA219 I2C_B_INA219_C(0x42);
Adafruit_INA219 I2C_B_INA219_D(0x43);
Adafruit_INA219 I2C_B_INA219_E(0x44);
Adafruit_INA219 I2C_B_INA219_F(0x45);
Adafruit_INA219 I2C_B_INA219_G(0x46);
Adafruit_INA219 I2C_B_INA219_H(0x47);
Adafruit_INA219 I2C_B_INA219_I(0x48);
Adafruit_INA219 I2C_B_INA219_J(0x49);
Adafruit_INA219 I2C_B_INA219_K(0x4A);
Adafruit_INA219 I2C_B_INA219_L(0x4B);
Adafruit_INA219 I2C_B_INA219_M(0x4C);
Adafruit_INA219 I2C_B_INA219_N(0x4D);
Adafruit_INA219 I2C_B_INA219_O(0x4E);
Adafruit_INA219 I2C_B_INA219_P(0x4F);
//Wifi Credentials
const char * SSID = "Avrupa";
const char * Password = "0749230994";

const char * Gateway_IP_Adress = "192.168.0.254";
//Task handle
xTaskHandle Scan_Gateway_Handle;
xTaskHandle Scan_Inputs_Handle;
//Create var for each INA 219
float I2C_A_Inputs_Intensity[16];
float I2C_A_Inputs_Tension[16];
float I2C_A_Inputs_Power[16];
byte I2C_A_Inputs_State[2]; // maximum of 16 INA_219 on one spi channel (2 * 16)

float I2C_B_Inputs_Intensity[16];
float I2C_B_Inputs_Tension[16];
float I2C_B_Inputs_Power[16];
byte I2C_B_Inputs_State[2]; // maximum of 16 INA_219 on one spi channel (2 * 16)
//Declare Functions
void Scan_Inputs(void *pvParameters);
void Scan_Gateway(void *pvParameters);

#endif