#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

class setupWiFi
{
    private:
        const char *ssid = "ESP32-Access-Point";
        const char *password = "123456789";
        #define LED_BUILTIN 2 // built-in LED

    public:
        setupWiFi(/* args */);
        ~setupWiFi();
        IPAddress getIP();
        void loop();
};
