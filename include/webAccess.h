#include <WebServer.h>
#include <ESPmDNS.h>
#include <SPI.h>
#include "SD.h"

class webAccess
{
private:
/*Vars*/
WebServer server;
bool hasSD = true;
File uploadFile;
const char* host = "ecg";
enum { sd_sck = 18, sd_miso = 19, sd_mosi = 23, sd_ss = 5 };
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
