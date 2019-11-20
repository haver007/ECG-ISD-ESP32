#include "setupWiFi.h"

setupWiFi::setupWiFi(/* args */)
{
    WiFi.softAP(ssid, password);
}

setupWiFi::~setupWiFi()
{
}

void setupWiFi::loop()
{
    while (1)
    {
    }
}

IPAddress setupWiFi::getIP()
{
    return WiFi.softAPIP();
}
