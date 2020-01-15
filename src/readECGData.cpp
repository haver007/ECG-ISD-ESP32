#include "readECGData.h"

readECGData::readECGData(/* args */)
{
    dataLock = xSemaphoreCreateMutex();
}

readECGData::~readECGData()
{
}
void readECGData::loop()
{
    while (1)
    {
    }
}