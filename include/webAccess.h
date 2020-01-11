#include <WebServer.h>
#include <ESPmDNS.h>
#include <SPI.h>
#include "mySD.h"

class webAccess
{
private:
/*Vars*/
WebServer server;
bool hasSD = false;
File uploadFile;
const char* host = "ecg";
/* Functions*/
void returnOK();
void returnFail(String msg);
bool loadFromSdCard(String path);
void handleFileUpload();
void deleteRecursive(String path);
void handleDelete();
void handleCreate();
void printDirectory();
void handleNotFound();

public:
    webAccess(/* args */);
    ~webAccess();
    void loop();
};
