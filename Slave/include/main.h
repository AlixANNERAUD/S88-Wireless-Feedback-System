#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

xTaskHandle Scan_Gateway_Handle;
xTaskHandle Scan_Inputs_Handle;

const byte Input_Pins[16] = {}

void Scan_Inputs(void *pvParameters);
void Scan_Gateway(void *pvParameters);

#endif