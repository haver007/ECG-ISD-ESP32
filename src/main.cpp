#include <Arduino.h>
#include <FreeRTOS.h>
#include "setupWiFi.h"
#include "onScreen.h"
#include "webAccess.h"

//declare Tasks
void taskScreen(void *parameter);
void taskWebServer(void *parameter);

//Declare Objects
setupWiFi *crtlWiFi;
onScreen *crtlScreen;
webAccess *crtlWeb;

//Vars
enum
{
  sd_sck = 18,
  sd_miso = 19,
  sd_mosi = 23,
  sd_ss = 5
};
SPIClass spiSd(HSPI);

void setup()
{
  //setup Serial for Debugging
  Serial.begin(9600);
  //Setup Objects

  crtlWiFi = new setupWiFi;
  crtlWiFi->turnOn(); //TODO move to MENU
                      // Give Time to Complete Wifi
  delay(2000);

  crtlScreen = new onScreen;
  spiSd.begin(sd_sck, sd_miso, sd_mosi, sd_ss);
  /* initialize SD library with SPI pins */
  if (SD.begin(sd_ss, spiSd, 24000000))
  {
    crtlWeb = new webAccess; //This should be done some where in Menu! TODO
  }
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
                    //CreateWebTask
  xTaskCreate(
      taskWebServer,   /* Task function. */
      "TaskWebServer", /* String with name of task. */
      5000,            /* Stack size in bytes. */
      NULL,            /* Parameter passed as input of the task */
      1,               /* Priority of the task. */
      NULL);           /* Task handle. */
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

void taskWebServer(void *parameter)
{
  crtlWeb->loop();
}