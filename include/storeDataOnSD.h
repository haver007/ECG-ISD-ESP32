#include <FreeRTOS.h>
#include <SD.h>

class storeDataOnSD
{
private:
    RingbufHandle_t buffer;
public:
    storeDataOnSD(RingbufHandle_t _buffer);
    ~storeDataOnSD();
    void loop();
};

