#include "ADAS1000.h"
#include <FreeRTOS.h>
#include <sstream>

class readECGData
{
private:
    SemaphoreHandle_t dataLock;
    RingbufHandle_t buffer;
    Leadformat format;
    ADAS1000 *adas1000;
    float read(void);

public:
    readECGData(RingbufHandle_t _buffer);
    ~readECGData();
    void initialize(int divider);
    void setFormat(Leadformat format);
    void loop();
    std::string getData();
};
