#include "setupWiFi.h"

setupWiFi::setupWiFi(/* args */)
{
}

setupWiFi::~setupWiFi()
{
}

IPAddress setupWiFi::getIP()
{
    return WiFi.softAPIP();
}

bool setupWiFi::turnOff()
{
    WiFi.softAPdisconnect(true);
}

bool setupWiFi::turnOn()
{
    WiFi.softAP(ssid, password);
}
