#include <SoftwareSerial.h>

#define Firmware_Version 0.01
#define Manufacture_Date 03/07/2019

byte PC = 2;  //Clock
byte PS = 3;  //Select
byte PDI = 0; //Data In
byte PDO = 1; //Data Out

int LT = 256; //Low Threesold
int HT = 768;

int clockCounter = 0;           // 16 tops

long loopCounter = 0;           //for reset from ECOS

unsigned int data=0xffff;     // buffer

byte SensorsStates[64] = 0;  // 512 / 8 = 64 Modules For S88, but only 20 with R-BUS

byte Modules = 2;                // nb sensors 8 or 16

byte FirstPin = 0;             // first pin
byte LastPin = 7;

SoftwareSerial SerialIn(10, 11);

void setup() {

    SerianIn.begin(115200);
    Serial.begin(115200);

    pinMode(Clock, INPUT_PULLUP);
    pinMode(PinSelect, INPUT_PULLUP);
    pinMode(DI, INPUT_PULLUP);       //pin 0 = data in from next Arduino S88 in chain
    pinMode(DO, OUTPUT);           //pin 1 = data out to ECoS or to previous Arduino in S88 chain

    attachInterrupt(0, clock, RISING);    //pin 2 = clock interrupt 0
    attachInterrupt(1, PS, RISING);       //pin 3 = PS interrupt 1

    while (!Serial) {

    }
}

void loop() {
  if(SerialIn.available()) {

  }

  if (loopCounter==20) {
    bitSet(sensors,0);
  }  // reset management

  for (byte i = FirstPin; i < 8; i++) {
    if (analogRead(i) < LT || analogRead(i) > HT ) {
      bitSet(sensors,i);
    }
  } // update sensors
}

void PS() {
    clockCounter=0;
    data=sensors;
    sensors=0;
    loopCounter++;
}

void clock() {
    digitalWrite(dataOut,bitRead(data,clockCounter)); // shift to next
    delayMicroseconds(16);
    bitWrite(data,clockCounter,digitalRead(dataIn)); // shift from previous
    clockCounter =(clockCounter +1) % nbsensors;     // modulo nb sensors
}

void serialEvent() {
  char Data;
  string Command = "";
  while (Serial.available()) {
    Data = Serial.read();
    Command += Data;
  }
  if (Command == "*GetInformations") {

  }
  if (Command == "*GetErros") {

  }
  if (Command == "*GetWarnings") {

  }
  else if (Command == "Informations") {

  }
  else {
    Serial.println(F("Unknow Command "));
  }
}
