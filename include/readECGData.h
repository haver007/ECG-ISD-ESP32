#include "ADAS1000.h"
#include <Arduino_FreeRTOS.h>

class readECGData
{
private:
SemaphoreHandle_t dataLock;
    /* data */
public:
    readECGData(/* args */);
    ~readECGData();
    void loop();
    std::string getData(); 
};
