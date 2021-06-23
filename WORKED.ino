#include <Arduino.h>

const byte clockS88 = 2;  // horloge du bus S88 pin = 2
int clockCounter = 0;     // compteur de tops horloge
const byte PSS88 = 3;     // signal PS du bus S88 pin = 3
long loopCounter = 0;     // reset proper à l’ECOS
const byte dataIn = 0;    // entrée des données depuis un autre Arduino dans
// la chaîne S88 pin = 0
const byte dataOut = 1;   // sortie des données vers un autre Arduino dans
// la chaîne ou vers la centrale pin=1
unsigned int sensors = 0; // tampon de 16 bits pour les capteurs
unsigned int data = 0xffff; // le registre à décalage
int nbsensors;            // nombre de capteurs  8 or 16
int beginPin = 4;         // première broche utilisée pour les capteurs
int endPin8 = 12;         // dernière broche pour  8 capteurs
int endPin16 = 21;        // dernière broche pour 16 capteurs
int endPin;               // variable locale

// routine d’interruption du signal PS
// (déclenchement d’un nouveau cycle d’horloge)

void PS() {
  clockCounter = 0;     // on remet le compteur à zéro
  data = sensors;       // on vide le tampon des capteurs dans le
  // registre à décalage
  sensors = 0;          // on remet à zéro le tampon des capteurs
  loopCounter++;        // on incrémente le nombre de top d’horloge
}

// routine d’interruption de l’horloge S88

void clock() {
  digitalWrite(dataOut, bitRead(data, clockCounter)); // on décale 1 bit en sortie
  delayMicroseconds(16);                            // délai pour le décalage
  bitWrite(data, clockCounter, digitalRead(dataIn)); // on décale 1 bit en entrée
  clockCounter = (clockCounter + 1) % nbsensors;    // modulo le nombre de capteurs
  // (8 ou 16)
}

// le setup S88

void setup() {
  nbsensors = 8;         // nombre de capteurs désirés (8 ou 16)
  if (nbsensors == 8) {           // MAJ des broches concernées
    endPin = endPin8;
  }
  else {
    endPin = endPin16;
  }
  pinMode(clockS88, INPUT_PULLUP); // init de la broche pour l’horloge
  attachInterrupt(0, clock, RISING); // horloge sur int 0 sur la broche 2
  pinMode(PSS88, INPUT_PULLUP);    // init de la broche du signal PS
  attachInterrupt(1, PS, RISING);  // PS sur int1 sur la broche 3
  pinMode(dataIn, INPUT_PULLUP);   // pin 0 = entrée des données depuis un
  // autre Arduino
  pinMode(dataOut, OUTPUT);        // pin 1 = sortie des données vers la
  // centrale ou vers un autre Arduino
  // dans le chaînage S88
  for (int i = beginPin; i < endPin; i++) {
    pinMode(i, INPUT_PULLUP);      // init des broches des capteurs
  }
}

// la boucle

void loop() {
  if (loopCounter == 20) {
    bitSet(sensors, 0);            // reset des tampons des capteurs pour l’ECOS
  }
  for (int i = 4; i < endPin; i++) { // MAJ des capteurs
    if (!digitalRead(i)) {
      bitSet(sensors, i - 4);
    }
  }
}
