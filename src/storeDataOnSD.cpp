#include "storeDataOnSD.h"

storeDataOnSD::storeDataOnSD(RingbufHandle_t _buffer)
{
    buffer=_buffer;
}

storeDataOnSD::~storeDataOnSD()
{
}

void storeDataOnSD::loop()
{
fs:File filer = SD.open("/ecg/record001.csv","rw");
    while (1)
    {
  size_t item_size;
    char *item = (char *)xRingbufferReceive(buffer, &item_size, pdMS_TO_TICKS(1000));
    filer.write(*item);

    }
}