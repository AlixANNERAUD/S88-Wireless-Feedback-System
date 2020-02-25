#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define NUMBER_SLAVE 2
#define NUMBER_SLAVE_INPUTS 16
#define UDP_PORT 8888

//Tasks Handle (not usefull here)
xTaskHandle Scan_Slave_Handle;

//Pins
const byte S88_Clock_Pin = 2;
const byte S88_PS_Pin = 3;
const byte S88_Data_Out_Pin = 1;

//Counters
byte S88_Selected_Slave = 0;
byte S88_Selected_Input = 0;
byte S88_Clock_Counter = 0;

//Modules IP 
const char * Slave_IP_Adress[NUMBER_SLAVE] = {"192.168.0.101", "192.168.0.102"};
//Module Input States
unsigned int Slave_Input_Register[NUMBER_SLAVE];

//WiFi network credentials
const char * SSID = "Avrupa";
const char * Password = "0749230994";

//Prototypes Of Functions
void Scan_Slave(void *pvParameters);
void S88_PS();
void S88_Clock();
#endif