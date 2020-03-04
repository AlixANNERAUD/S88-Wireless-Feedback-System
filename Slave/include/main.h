#include <Adafruit_INA219.h>
#include <Wire.h>

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#define UDP_PORT 8888
#define I2C_A_SDA 27
#define I2C_A_SCL 26
#define I2C_B_SDA 33
#define I2C_B_SCL 32
#define NUMBER_INPUTS_I2C_A 1
#define NUMBER_INPUTS_I2C_B 1

TwoWire I2C_A = TwoWire(0);
TwoWire I2C_B = TwoWire(1);

Adafruit_INA219 I2C_A_INA219_A(0x40);

Adafruit_INA219 I2C_B_INA219_A(0x40);

const char * SSID = "Avrupa";
const char * Password = "0749230994";

xTaskHandle Scan_Gateway_Handle;
xTaskHandle Scan_Inputs_Handle;

const float I2C_A_Input_Intensity[NUMBER_INPUTS_I2C_A];
const byte I2C_A_Input_Tension[NUMBER_INPUTS_I2C_A];

const byte I2C_B_Input_Intensity[NUMBER_INPUTS_I2C_B];
const byte I2C_B_Input_Tension[NUMBER_INPUTS_I2C_B];

void Scan_Inputs(void *pvParameters);
void Scan_Gateway(void *pvParameters);

#endif