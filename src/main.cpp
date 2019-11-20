#include <Arduino.h>
#include <FreeRTOS.h>
#include "setupWiFi.h"
#include "onScreen.h"

void taskScreen(void *parameter);
void taskTwo(void *parameter);
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
      10000,        /* Stack size in bytes. */
      NULL,         /* Parameter passed as input of the task */
      1,            /* Priority of the task. */
      NULL);        /* Task handle. */

  xTaskCreate(
      taskTwo,   /* Task function. */
      "TaskTwo", /* String with name of task. */
      10000,     /* Stack size in bytes. */
      NULL,      /* Parameter passed as input of the task */
      1,         /* Priority of the task. */
      NULL);     /* Task handle. */
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

void taskTwo(void *parameter)
{

  for (int i = 0; i < 10; i++)
  {

    Serial.println("Hello from task 2");
    Serial.print("loop() running on core ");
    Serial.println(xPortGetCoreID());
    delay(1000);
  }
  Serial.println("Ending task 2");
  vTaskDelete(NULL);
}