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

readECGData* ctrlECG;
setupWiFi* crtlWiFi;
onScreen* crtlScreen;
webAccess* crtlWeb;
storeDataOnSD* crtlStore;

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
  dataBuffer = xRingbufferCreate(8196, RINGBUF_TYPE_BYTEBUF);
  //Setup Objects

  crtlWiFi = new setupWiFi();
  crtlWiFi->turnOn(); //TODO move to MENU
                      // Give Time to Complete Wifi
  delay(5000);
  // crtlScreen = std::make_shared<onScreen>();
  spiSd.begin(sd_sck, sd_miso, sd_mosi, sd_ss);
  //initialize SD library with SPI pins
  if (SD.begin(sd_ss, spiSd, 24000000))
  {
    crtlWeb = new webAccess(); //This should be done some where in Menu! TODO
  }

  crtlStore = new storeDataOnSD(dataBuffer);
  ctrlECG = new readECGData(dataBuffer);
  ctrlECG->initialize(2);

  //xTaskCreate(taskScreen, "TaskScreen",5000, NULL, 1, NULL);
	xTaskCreatePinnedToCore(taskECG,"ReadECGData", 5000, nullptr, 1, nullptr, 0);
  //xTaskCreate(taskECG,"ReadECGData", 5000, nullptr, 1, nullptr);
 // xTaskCreate(taskWebServer, "TaskWebServer",5000, nullptr, 1, nullptr);
  xTaskCreate(taskStore, "TaskStore", 5000, NULL, 1, NULL);
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