#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct addrinfo* result = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        printf("bind() mislukt: %d\n", WSAGetLastError());
        return 1;
    }
    freeaddrinfo(result);

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen() mislukt: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Server luistert op poort %s...\n", DEFAULT_PORT);

    SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept() mislukt: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Client verbonden!\n");
    closesocket(ListenSocket);

    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    do {
        iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN - 1, 0);
        if (iResult > 0) {
            recvbuf[iResult] = '\0';
            printf("Ontvangen: %s\n", recvbuf);
            const char* antwoord = "Hallo van de server!";
            send(ClientSocket, antwoord, (int)strlen(antwoord), 0);
        }
    } while (iResult > 0);

    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}