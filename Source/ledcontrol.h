#ifndef ledcontrol_h
#define ledcontrol_h

#include "BluetoothSerial.h"
#include <string.h> 
#include <unistd.h>



#define device_number 0x41 // device number
#define PIN_RED    23 // GIOP23
#define PIN_GREEN  22 // GIOP22
#define PIN_BLUE   21 // GIOP21
#define PIN_REDCHECK 4 // GPIO4
#define PIN_GREENCHECK 2 // GPIO2
#define PIN_BLUECHECK 33 //GPIO15
#define PIN_RGBANODE 17 // 3.3v led
#define AUTOMODE  0x41
#define MANUALMODE  0x42

void bluetoothTask();
void autoAdjustTask();
unsigned int crc16(char* msg,unsigned int len);

#endif
