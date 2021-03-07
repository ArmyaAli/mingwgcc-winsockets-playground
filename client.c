#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

int main(void)
{
    int sock; /* Socket descriptor */
    int recv_size; // size of reciving buffer
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short serverPort;     // server port
    char* servIP;                    /* Server IP address (dotted quad) */
    int messageLen;                  /* Length of string to echo */
    WSADATA wsaData;                 /* Structure for WinSock setup communication */
    char server_reply[2000];
    char* message;
    servIP       = "127.0.0.1"; /* First arg: server IP address (dotted quad) */
    serverPort = 8888;      /* Use given port, if any */

    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
    {
        fprintf(stderr, "WSAStartup() failed");
        exit(1);
    }

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Crashed at socket created");
    }

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */

    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(serverPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr)) < 0)
    {
        printf("Crashed at connect\n");
        exit(1);
    }
    
    /* Send the string, including the null terminator, to the server */
    if (send(sock, message, messageLen, 0) != messageLen)
    {
        printf("Crashed at send");
        exit(1);
    }

    // Receive a reply from the server
    if ((recv_size = recv(sock, server_reply, 2000, 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }

    puts("Reply received\n");

    // Add a NULL terminating character to make it a proper string before printing
    server_reply[recv_size] = '\0';
    puts(server_reply);
    closesocket(sock);
    WSACleanup(); /* Cleanup Winsock */

    return 0;
}
