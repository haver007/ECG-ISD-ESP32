#include "webAccess.h"
#include "setupWiFi.h"

WiFiServer server(80);

webAccess::webAccess(/* args */)
{
    server.begin();
    Serial.println("Server started");

}

webAccess::~webAccess()
{
}

void webAccess::loop()
{
    while (1)
    {
        WiFiClient client = server.available(); // listen for incoming clients
        if (client)
        {                                      // if you get a client,
            Serial.println("\nNew Client.\n"); // print a message out the serial port
            Serial.print("Client connected with IP:");
            Serial.println(client.remoteIP());
            String currentLine = ""; // make a String to hold incoming data from the client
            while (client.connected())
            { // loop while the client's connected
                if (client.available())
                {                           // if there's bytes to read from the client,
                    char c = client.read(); // read a byte, then
                    Serial.write(c);        // print it out the serial monitor
                    if (c == '\n')
                    { // if the byte is a newline character
                        // if the current line is blank, you got two newline characters in a row.
                        // that's the end of the client HTTP request, so send a response:
                        if (currentLine.length() == 0)
                        {
                            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                            // and a content-type so the client knows what's coming, then a blank line:
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-type:text/html");
                            client.println();

                            // the content of the HTTP response follows the header:
                            client.println("Welcome to ECG project!\n");
                            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
                            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>"); // "here" = hyperlink
                            // client.print("Click <a href=\"/O\">here</a> to turn OFF WIFI.<br>");
                            // The HTTP response ends with another blank line:
                            client.println();
                            // break out of the while loop:
                            break;
                        }
                        else
                        { // if you got a newline, then clear currentLine:
                            currentLine = "";
                        }
                    }
                    else if (c != '\r')
                    {                     // if you got anything else but a carriage return character,
                        currentLine += c; // add it to the end of the currentLine
                    }

                    // Check to see if the client request was "GET /H" or "GET /L":
                    if (currentLine.endsWith("GET /H"))
                    {
                        digitalWrite(LED_BUILTIN, HIGH); // GET /H turns the LED on
                    }
                    if (currentLine.endsWith("GET /L"))
                    {
                        digitalWrite(LED_BUILTIN, LOW); // GET /L turns the LED off
                    }
                    /* if (currentLine.endsWith("GET /O"))
                {
                    WiFi.mode(WIFI_OFF);
                } */
                }
            }
            // close the connection:
            client.stop();
            Serial.println("Client Disconnected.\n");
        }
    }
}