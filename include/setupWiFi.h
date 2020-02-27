#include <WiFi.h>

class setupWiFi
{
private:
    const char *ssid = "ESP32-Access-Point_Gerrit";
    const char *password = "123456789";

public:
    setupWiFi(/* args */);
    ~setupWiFi();
    IPAddress getIP();
    bool turnOff();
    bool turnOn();

};
