#include <stdio.h>
#include <windows.h>
#include <winsock2.h>

typedef struct socketData
{
    SOCKET client, server;
    struct sockaddr_in sockaddr_server, sockaddr_client;
} sockdata;

DWORD WINAPI handleServerRequest(void* data);

int main(void)
{
    WSADATA wsa;
    sockdata sockData;
    int port = 8888;
    int c;

    printf("\nInitialising Winsock...");

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    // Create a socket
    if ((sockData.server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");

    // Prepare the sockaddr_in structure
    sockData.sockaddr_server.sin_family      = AF_INET;
    sockData.sockaddr_server.sin_addr.s_addr = INADDR_ANY;
    sockData.sockaddr_server.sin_port        = htons(port);

    // Bind the socket to the correct network request
    if (bind(sockData.server, (struct sockaddr*)&sockData.sockaddr_server, sizeof(sockData.sockaddr_server)) ==
        SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }

    // listen for a response.
    while (1)
    {
        printf("Listening for requests...\n");
        listen(sockData.server, 3);
        sockData.client = accept(sockData.server, (struct sockaddr*)&sockData.sockaddr_client, &c);
        printf("Accepted a request...\n");
        HANDLE thread = CreateThread(NULL, 0, handleServerRequest, (void*)&sockData, 0, NULL);
        if (thread)
        {
            printf("Passing job to thread...\n");
        }
    }

    closesocket(sockData.server);

    return 0;
}

DWORD WINAPI handleServerRequest(void* data)
{

    int c = sizeof(struct sockaddr_in);

    sockdata sockData             = *(sockdata*)data;
    const char* messageToSendBack = "<div>Hello World</div>";

    if (sockData.client == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d", WSAGetLastError());
    }
    puts("Sending some data back lol");

    /* Send the string, including the null terminator, to the server */
    if (send(sockData.client, messageToSendBack, strlen(messageToSendBack), 0) != strlen(messageToSendBack))
    {
        printf("Crashed at send");
        exit(1);
    }
    printf("Finished sending back data to client\n");
    return 0;
}