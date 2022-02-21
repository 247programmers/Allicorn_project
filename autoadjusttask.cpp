#include "Arduino.h"
#include "ledcontrol.h"

extern BluetoothSerial SerialBT;
extern char temp[256];
extern void setColor(int channel0, int channel1, int channel2);
extern unsigned char RGBarray[7][3];
extern unsigned char colormode;
extern unsigned char brightmode;
extern unsigned char brightness;

void autoAdjust()
{
  
}
