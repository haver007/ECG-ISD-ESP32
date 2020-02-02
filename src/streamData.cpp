#include "streamData.h"

streamData::streamData(/* args */)
{
}

streamData::~streamData()
{
}

void streamData::loop()
{
    while (1)
    {
        /* Create a listening socket.  We then wait for a client to connect.
        Once a client has connected, we then read until there is no more data
        and log the data read.  We then close the client socket and start 
        waiting for a new connection. */
        struct sockaddr_in clientAddress;
        struct sockaddr_in serverAddress;

        // Create a socket that we will listen upon.
        int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock < 0)
        {
            ESP_LOGE(tag, "socket error: %d %s", sock, strerror(errno));
            // do not use "goto" since it bypasses variable initialisations
            // instead use the Task directly
            vTaskDelete(NULL);
        }

        // Bind our server socket to a port.
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddress.sin_port = htons(PORT_NUMBER);
        int rc = bind(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
        if (rc < 0)
        {
            ESP_LOGE(tag, "bind error: %d %s", rc, strerror(errno));
            vTaskDelete(NULL);
        }

        // Flag the socket as listening for new connections.
        rc = listen(sock, 5);
        if (rc < 0)
        {
            ESP_LOGE(tag, "listen error: %d %s", rc, strerror(errno));
            vTaskDelete(NULL);
        }

        while (1)
        {
            // Listen for a new client connection.
            socklen_t clientAddressLength = sizeof(clientAddress);
            int clientSock = accept(sock, (struct sockaddr *)&clientAddress, &clientAddressLength);
            if (clientSock < 0)
            {
                ESP_LOGE(tag, "accept error: %d %s", clientSock, strerror(errno));
                vTaskDelete(NULL);
            }

            // We now have a new client ...
            int total = 10 * 1024;
            int sizeUsed = 0;
            char *data = (char *)malloc(total);

            // Loop reading data.
            while (1)
            {
                ssize_t sizeRead = recv(clientSock, data + sizeUsed, total - sizeUsed, 0);
                if (sizeRead < 0)
                {
                    ESP_LOGE(tag, "recv error: %d %s", sizeRead, strerror(errno));
                    vTaskDelete(NULL);
                }
                if (sizeRead == 0)
                {
                    break;
                }
                sizeUsed += sizeRead;
            }

            // Finished reading data.
            ESP_LOGD(tag, "Data read (size: %d) was: %.*s", sizeUsed, sizeUsed, data);
            free(data);
            close(clientSock); // close socket
        }
    }
}