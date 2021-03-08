#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

int main(void)
{
    int recv_size = 0;
    struct sockaddr_in echoServAddr;
    SOCKET sock;
    unsigned short serverPort;
    char* servIP;
    int messageLen;
    WSADATA wsaData;
    char server_reply[2000];
    char* message;
    servIP     = "127.0.0.1"; // loopback
    serverPort = 8888;

    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
    {
        fprintf(stderr, "WSAStartup() failed");
        exit(1);
    }

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Crashed at socket created");
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));

    echoServAddr.sin_family      = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port        = htons(serverPort);

    /* establish connection */
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
