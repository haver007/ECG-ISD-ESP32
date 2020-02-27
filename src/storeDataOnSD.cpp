#include "storeDataOnSD.h"

storeDataOnSD::storeDataOnSD(RingbufHandle_t _buffer)
{
    buffer = _buffer;
}

storeDataOnSD::~storeDataOnSD()
{
}

void storeDataOnSD::loop()
{
    if (!SD.exists("/recordings"))
    {
        SD.mkdir("/recordings");
    }
File filer = SD.open("/recordings/record001.csv", FILE_WRITE);
    while (1)
    {
        size_t item_size;
        uint8_t *item;
        item = static_cast<uint8_t *>(xRingbufferReceive(buffer, &item_size, 10));

        //Check received item
        if (item != NULL)
        {
            
            size_t a = filer.write(item,item_size);
           // Serial.printf("%d \n ", a);
            filer.flush();
            vRingbufferReturnItem(buffer,(void*)item);
            vTaskDelay(20);
        }
    }
       filer.close();
}