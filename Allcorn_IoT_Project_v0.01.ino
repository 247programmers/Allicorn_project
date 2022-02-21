#include "ledcontrol.h"

/* global variable start*/
BluetoothSerial SerialBT;

char temp[256];
int tt = 0;

unsigned char colormode;
unsigned char brightmode;
unsigned char brightness;

unsigned char RGBarray[7][3] = { {0,255,255}, {0,205,255}, {0,0,255},
{255,0,255}, {255,255,0},{255,250,0},{155,255,0}
}; // red , orange, yellow, green, blue, indigo, purple

/* global variable end*/

void setColor(int channel0, int channel1, int channel2)
{
  ledcWrite(0, channel0);
  ledcWrite(1, channel1);
  ledcWrite(2, channel2);
}

void taskForBLE(void *parameter)
{
  while(1){
      bluetoothTask();
  }
 
}

void taskForAutoAdjust(void * parameter)
{
  while (true) {
    micros();

    if (tt==20){

    }
    delay(10);
  }
}

void taskForWifi(void * parameter)
{
  while (true) {
    micros();
    tt++;
    if (tt>100)
    {
      tt=0;
    }

    delay(100);
  }
}

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

void setup() {
  colormode = 0x41;
  brightmode = 0x41;
  brightness = 255;
  ledcAttachPin(PIN_RED, 0);
  ledcAttachPin(PIN_GREEN, 1);
  ledcAttachPin(PIN_BLUE, 2);
  pinMode(PIN_RGBANODE, OUTPUT);
  SerialBT.begin("device0x41");
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  Serial.begin(9600);
  
  digitalWrite(PIN_RGBANODE,1);
  setColor(0,0,0);
  delay(100);

  xTaskCreatePinnedToCore(
    taskForBLE,             /* pvTaskCode */
    "Workload1",            /* pcName */
    1000,                   /* usStackDepth */
    NULL,                   /* pvParameters */
    1,                      /* uxPriority */
    &Task1,                 /* pxCreatedTask */
    0);                     /* xCoreID */

    xTaskCreatePinnedToCore(
    taskForAutoAdjust,                  /* pvTaskCode */
    "Workload1",            /* pcName */
    1000,                   /* usStackDepth */
    NULL,                   /* pvParameters */
    1,                      /* uxPriority */
    &Task2,                 /* pxCreatedTask */
    0);                     /* xCoreID */

    
    xTaskCreatePinnedToCore(
    taskForWifi,         /* pvTaskCode */
    "Workload1",            /* pcName */
    1000,                   /* usStackDepth */
    NULL,                   /* pvParameters */
    1,                      /* uxPriority */
    &Task3,                 /* pxCreatedTask */
    0);                     /* xCoreID */
}

void loop() {

}
