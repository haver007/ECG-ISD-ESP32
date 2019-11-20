#include "setupWiFi.h"

setupWiFi::setupWiFi(/* args */)
{
    WiFi.softAP(ssid, password);
}

setupWiFi::~setupWiFi()
{
}

IPAddress setupWiFi::getIP()
{
    return WiFi.softAPIP();
}
