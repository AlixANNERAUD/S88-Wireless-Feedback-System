#include <Arduino.h>


void S88_Clock();
void S88_PS();
//pins
const byte S88_Clock_Pin = 2;
const byte S88_PS_Pin = 13;
const byte S88_Data_Out_Pin = 4;
//counters
byte S88_Selected_Slave = 0;
byte S88_Selected_Input = 0;
int S88_Clock_Counter = 0;
//Inputs register
byte Inputs_Register[2];

void setup() {
  Inputs_Register[0] = B10011101;
  Inputs_Register[1] = B10101010;

  //Inputs_Register[0] = B10101011;
  //Inputs_Register[1] = B10111101;
  Serial.begin(115200);
  Serial.print(F("ESP32 S88 Test"));

  pinMode(S88_Clock_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(S88_Clock_Pin), S88_Clock, RISING);
  pinMode(S88_PS_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(S88_PS_Pin), S88_PS, RISING);
  pinMode(S88_Data_Out_Pin, OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

void S88_PS() {
  
  Serial.println(S88_Selected_Slave);
  S88_Selected_Slave = 0;
  S88_Selected_Input = 0;
}

void S88_Clock() {
  digitalWrite(S88_Data_Out_Pin, bitRead(Inputs_Register[S88_Selected_Slave], S88_Selected_Input));
  S88_Selected_Input++;

  if(S88_Selected_Input > 7) {
    S88_Selected_Input = 0;
    S88_Selected_Slave++;
  }
}