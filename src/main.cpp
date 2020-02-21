#include <Arduino.h>
#include <FreeRTOS.h>
#include "setupWiFi.h"
#include "onScreen.h"
#include "webAccess.h"
#include "readECGData.h"
#include "storeDataOnSD.h"


//declare Tasks
void taskScreen(void *parameter);
void taskWebServer(void *parameter);
void taskECG(void *parameter);
void taskStore(void *parameter);

//Declare Objects

std::shared_ptr<readECGData> ctrlECG;
std::shared_ptr<setupWiFi> crtlWiFi;
std::shared_ptr<onScreen> crtlScreen;
std::shared_ptr<webAccess> crtlWeb;
std::shared_ptr<storeDataOnSD> crtlStore;

//Vars
enum
{
  sd_sck = 18,
  sd_miso = 19,
  sd_mosi = 23,
  sd_ss = 5
};

RingbufHandle_t dataBuffer;

SPIClass spiSd(VSPI);

void setup()
{
  //setup Serial for Debugging
  Serial.begin(9600);
  // Setup Vars
  dataBuffer = xRingbufferCreate(1028, RINGBUF_TYPE_NOSPLIT);
  //Setup Objects
  
  crtlWiFi = std::make_shared<setupWiFi>();
  crtlWiFi->turnOn(); //TODO move to MENU
                      // Give Time to Complete Wifi
  delay(2000);
 // crtlScreen = std::make_shared<onScreen>();
  spiSd.begin(sd_sck, sd_miso, sd_mosi, sd_ss);
  //initialize SD library with SPI pins 
   if (SD.begin(sd_ss, spiSd, 2400000))
   {
     crtlWeb = std::make_shared<webAccess>(); //This should be done some where in Menu! TODO
   }

  crtlStore = std::make_shared<storeDataOnSD>(dataBuffer);
  ctrlECG = std::make_shared<readECGData>(dataBuffer);
  ctrlECG->initialize(4);


  //Create Display Task
 // xTaskCreate(
   //   taskScreen,   /* Task function. */
//      "TaskScreen", /* String with name of task. */
//      5000,         /* Stack size in bytes. */
//      NULL,         /* Parameter passed as input of the task */
//      1,            /* Priority of the task. */
//      NULL);        /* Task handle. */
                    //CreateWebTask
         /* Task handle. */
 xTaskCreate(
    taskECG,   /* Task function. */
  "TaskECG", /* String with name of task. */
      400000,            /* Stack size in bytes. */
      NULL,            /* Parameter passed as input of the task */
      1,               /* Priority of the task. */
      NULL);           /* Task handle. */
      
        xTaskCreate(
      taskWebServer,   /* Task function. */
      "TaskWebServer", /* String with name of task. */
      5000,            /* Stack size in bytes. */
      NULL,            /* Parameter passed as input of the task */
      1,               /* Priority of the task. */
      NULL);  
 xTaskCreate(
    taskStore,   /* Task function. */
  "TaskStore", /* String with name of task. */
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

void taskECG(void *parameter)
{
  ctrlECG->loop();
}
void taskStore(void *parameter)
{
  crtlStore->loop();
}