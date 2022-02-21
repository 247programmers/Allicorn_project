#include "Arduino.h"
#include "ledcontrol.h"

extern BluetoothSerial SerialBT;
extern char temp[256];
extern void setColor(int channel0, int channel1, int channel2);
extern unsigned char RGBarray[7][3];
extern unsigned char colormode;
extern unsigned char brightmode;
extern unsigned char brightness;

unsigned char temp2[256];

//crc checksum
static uint16_t MODBUS_CRC16_v1( const unsigned char *buf, unsigned int len )
{
  uint16_t crc = 0xFFFF;
  unsigned int i = 0;
  char bit = 0;

  for( i = 0; i < len; i++ )
  {
    crc ^= buf[i];

    for( bit = 0; bit < 8; bit++ )
    {
      if( crc & 0x0001 )
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }

  return crc;
}

void bluetoothTask()
{
   micros(); // update overflow
   if (SerialBT.available()){
    SerialBT.readString().toCharArray(temp,256);
    for (int i =0 ; i <256; i++)
    {
      temp2[i] = temp[i];
    }
    Serial.println(temp);
    Serial.print(strlen(temp));
    unsigned char test_data[6] = {0x01, 0x03, 0x00, 0x02, 0x00, 0x02};
    Serial.println(MODBUS_CRC16_v1(test_data,6)>>8,HEX);

        
    if (temp[0] == device_number)
    {
      if (temp[1] == 0x41) //set color
      {
        if (temp[2] <= 0x47 && temp[2] >= 0x41)
        {
          if ((MODBUS_CRC16_v1(temp2,3)>>8 == temp2[3]) && ((MODBUS_CRC16_v1(temp2,3) & 0x00FF) == temp2[4]))
          {
            if (colormode == MANUALMODE)
              setColor(RGBarray[temp[2]-0x41][0],RGBarray[temp[2]-0x41][1],RGBarray[temp[2]-0x41][2]);
          }
          else
          {
            Serial.println("check CRC16 modbus..");
          }
        }
        else
        {
          Serial.println("check color...");
        }
      }
      else if (temp[1] == 0x42) //set colormode
      {
        if (temp[2] == 0x41 || temp[2] == 0x42)
        {  
          if ((MODBUS_CRC16_v1(temp2,3)>>8 == temp2[3]) && ((MODBUS_CRC16_v1(temp2,3) & 0x00FF) == temp2[4]))
          {
            colormode = temp2[2];
          }
          else
          {
            Serial.println("check CRC16 modbus..");
          }
        }
      }
      else if (temp[1] == 0x43) // set brightness
      {
        if (brightmode == MANUALMODE)
        {
          if ((MODBUS_CRC16_v1(temp2,3)>>8 == temp2[3]) && ((MODBUS_CRC16_v1(temp2,3) & 0x00FF) == temp2[4]))
          {
            brightness = temp2[2];
            Serial.println("brightness was changed..");
            Serial.println(brightness,HEX);
          }          
        }
      }
      else if (temp[1] == 0x44) // set brightnessmode
      {

        if (temp[2] == 0x41 || temp[2] == 0x42)
        {  
          if ((MODBUS_CRC16_v1(temp2,3)>>8 == temp2[3]) && ((MODBUS_CRC16_v1(temp2,3) & 0x00FF) == temp2[4]))
          {
            brightmode = temp2[2];
            Serial.println("brightmode was changed,,");
          }
          else
          {
            Serial.println("check CRC16 modbus..");
          }
        }
        
      }
      else if (temp[1] == 0x45) // turn light on or off
      {
        if (temp[2] == 0x41)
        {
           if ((MODBUS_CRC16_v1(temp2,3)>>8 == temp2[3]) && ((MODBUS_CRC16_v1(temp2,3) & 0x00FF) == temp2[4]))
           {
              digitalWrite(PIN_RGBANODE,1);
              Serial.println("turn light on");
           }
        }
        else if (temp[2] == 0x42)
        {
           if ((MODBUS_CRC16_v1(temp2,3)>>8 == temp2[3]) && ((MODBUS_CRC16_v1(temp2,3) & 0x00FF) == temp2[4]))
           {
              digitalWrite(PIN_RGBANODE,0);
              Serial.println("turn light off");
           }
        }
        
      }      
      else if (temp[1] == 0x46) // scan LED state
      {
        Serial.println("color : ");
        Serial.println("brightness : ");
        Serial.println("light : ");
      }
      else
      {
        Serial.println("check function code");
      }

    }
    else
    {
      Serial.println("please check device number");
    }
    
   }
   delay(1);

   
}
