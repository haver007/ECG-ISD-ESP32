#include <Arduino.h>
#include <FreeRTOS.h>
#include "setupWiFi.h"
#include "onScreen.h"
//declare Tasks
void taskScreen(void *parameter);

//Declare Objects
setupWiFi *crtlWiFi;
onScreen *crtlScreen;

void setup()
{
  //setup Serial for Debugging
  Serial.begin(9600);
  //Setup Objects
  crtlWiFi = new setupWiFi;
  crtlScreen = new onScreen;
  // Give Time to Complete Wifi
  delay(2000);
  //Create Display Task
  xTaskCreate(
      taskScreen,   /* Task function. */
      "TaskScreen", /* String with name of task. */
      5000,         /* Stack size in bytes. */
      NULL,         /* Parameter passed as input of the task */
      1,            /* Priority of the task. */
      NULL);        /* Task handle. */
}

void loop()
{
  //Just do nothing
  delay(1000);
}

void taskScreen(void *parameter)
{
  crtlScreen->loop();
}