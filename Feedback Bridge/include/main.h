#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

uint8_t Bridge_MAC_Adress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //useless here, just for a memo

const char * Module_1_IP_Adress = "192.168.0.101";
const int UDP_Port;
//WiFi network credentials
const char * SSID = "Avrupa";
const char * Password = "0749230994";

uint8_t Ask

WiFiUDP UDP;


class Slave_Module {
    private:

    public:

}


Slave_Module Module_1;

//etc ....

void Tranmit();
void Receive();

#endif