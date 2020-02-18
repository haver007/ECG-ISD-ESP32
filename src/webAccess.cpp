#include "webAccess.h"

webAccess::webAccess(/* args */) : server(80)
{
    if (MDNS.begin(host))
    {
        MDNS.addService("http", "tcp", 80);
    }

    server.on("/list", HTTP_GET, std::bind(&webAccess::printDirectory, this));
    server.on("/edit", HTTP_DELETE, std::bind(&webAccess::handleDelete, this));
    server.on("/edit", HTTP_PUT, std::bind(&webAccess::handleCreate, this));
    server.on("/edit", HTTP_POST, std::bind(&webAccess::handleFileUpload, this));
    server.onNotFound(std::bind(&webAccess::handleNotFound, this));
    server.begin();

    
}

webAccess::~webAccess()
{
    server.stop();
}

void webAccess::loop()
{
    while (1)
    {
        server.handleClient();
    }
}

void webAccess::returnOK()
{
    server.send(200, "text/plain", "");
}

void webAccess::returnFail(String msg)
{
    server.send(500, "text/plain", msg + "\r\n");
}

bool webAccess::loadFromSdCard(String path)
{
    String dataType = "text/plain";
    if (path.endsWith("/"))
        path += "index.htm";

    if (path.endsWith(".src"))
        path = path.substring(0, path.lastIndexOf("."));
    else if (path.endsWith(".htm"))
        dataType = "text/html";
    else if (path.endsWith(".css"))
        dataType = "text/css";
    else if (path.endsWith(".js"))
        dataType = "application/javascript";
    else if (path.endsWith(".png"))
        dataType = "image/png";
    else if (path.endsWith(".gif"))
        dataType = "image/gif";
    else if (path.endsWith(".jpg"))
        dataType = "image/jpeg";
    else if (path.endsWith(".ico"))
        dataType = "image/x-icon";
    else if (path.endsWith(".xml"))
        dataType = "text/xml";
    else if (path.endsWith(".pdf"))
        dataType = "application/pdf";
    else if (path.endsWith(".zip"))
        dataType = "application/zip";

    File dataFile = SD.open(path.c_str());
    if (dataFile.isDirectory())
    {
        path += "/index.htm";
        dataType = "text/html";
        dataFile = SD.open(path.c_str());
    }

    if (!dataFile)
        return false;

    if (server.hasArg("download"))
    {
        dataType = "application/octet-stream";
    }

    if (server.streamFile(dataFile, dataType) != dataFile.size())
    {
    }

    dataFile.close();
    return true;
}

void webAccess::handleFileUpload()
{
    returnOK();
    if (server.uri() != "/edit")
    {
        return;
    }
    HTTPUpload &upload = server.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
        if (SD.exists((char *)upload.filename.c_str()))
        {
            SD.remove((char *)upload.filename.c_str());
        }
        uploadFile = SD.open(upload.filename.c_str(), FILE_WRITE);
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
        if (uploadFile)
        {
            uploadFile.write(upload.buf, upload.currentSize);
        }
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
        if (uploadFile)
        {
            uploadFile.close();
        }
    }
}
void webAccess::deleteRecursive(String path)
{
    File file = SD.open((char *)path.c_str());
    if (!file.isDirectory())
    {
        file.close();
        SD.remove((char *)path.c_str());
        return;
    }

    file.rewindDirectory();
    while (true)
    {
        File entry = file.openNextFile();
        if (!entry)
        {
            break;
        }
        String entryPath = path + "/" + entry.name();
        if (entry.isDirectory())
        {
            entry.close();
            deleteRecursive(entryPath);
        }
        else
        {
            entry.close();
            SD.remove((char *)entryPath.c_str());
        }
        yield();
    }

    SD.rmdir((char *)path.c_str());
    file.close();
}

void webAccess::handleDelete()
{
    if (server.args() == 0)
    {
        return returnFail("BAD ARGS");
    }
    String path = server.arg(0);
    if (path == "/" || !SD.exists((char *)path.c_str()))
    {
        returnFail("BAD PATH");
        return;
    }
    deleteRecursive(path);
    returnOK();
}

void webAccess::handleCreate()
{
    if (server.args() == 0)
    {
        return returnFail("BAD ARGS");
    }
    String path = server.arg(0);
    if (path == "/" || SD.exists((char *)path.c_str()))
    {
        returnFail("BAD PATH");
        return;
    }

    if (path.indexOf('.') > 0)
    {
        File file = SD.open((char *)path.c_str(), FILE_WRITE);
        if (file)
        {
            file.write(NULL, 0);
            file.close();
        }
    }
    else
    {
        SD.mkdir((char *)path.c_str());
    }
    returnOK();
}

void webAccess::printDirectory()
{
    if (!server.hasArg("dir"))
    {
        return returnFail("BAD ARGS");
    }
    String path = server.arg("dir");
    if (path != "/" && !SD.exists((char *)path.c_str()))
    {
        return returnFail("BAD PATH");
    }
    File dir = SD.open((char *)path.c_str());
    path.clear();
    if (!dir.isDirectory())
    {
        dir.close();
        return returnFail("NOT DIR");
    }
    dir.rewindDirectory();
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/json", "");
    WiFiClient client = server.client();

    server.sendContent("[");
    for (int cnt = 0; true; ++cnt)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            break;
        }

        String output;
        if (cnt > 0)
        {
            output = ',';
        }

        output += "{\"type\":\"";
        output += (entry.isDirectory()) ? "dir" : "file";
        output += "\",\"name\":\"";
        output += entry.name();
        output += "\"";
        output += "}";
        server.sendContent(output);
        entry.close();
    }
    server.sendContent("]");
    server.sendContent(""); // Terminate the HTTP chunked transmission with a 0-length chunk
    dir.close();
}

void webAccess::handleNotFound()
{
    if (hasSD && loadFromSdCard(server.uri()))
    {
        return;
    }
    String message = "SDCARD Not Detected\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}