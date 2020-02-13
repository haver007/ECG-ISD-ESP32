#include "ADAS1000.h"
#include <FreeRTOS.h>

class readECGData
{
private:
    SemaphoreHandle_t dataLock;
    Leadformat format;
    ADAS1000 *adas1000;
    float read(void);

public:
    readECGData(RingbufHandle_t &buffer);
    ~readECGData();
    void initialize(int divider);
    void setFormat(Leadformat format);
    void loop();
    std::string getData();
};
