#include "setupWiFi.h"

setupWiFi::setupWiFi(/* args */)
{

    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    Serial.println();
    Serial.println("Configuring access point...");

    // You can remove the password parameter if you want the AP to be open.
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
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