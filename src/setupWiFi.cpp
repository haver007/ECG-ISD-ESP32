#include "setupWiFi.h"

setupWiFi::setupWiFi(/* args */)
{
}

setupWiFi::~setupWiFi()
{
    turnOff();
}

IPAddress setupWiFi::getIP()
{
    return WiFi.softAPIP();
}

bool setupWiFi::turnOff()
{
   return  WiFi.softAPdisconnect(true);
}

bool setupWiFi::turnOn()
{
   return WiFi.softAP(ssid, password);
}
