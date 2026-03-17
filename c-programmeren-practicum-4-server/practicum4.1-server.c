#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

const char* zoekWaarde(const char* key) {
    if (strcmp(key, "temperatuur") == 0)        return "22.5";
    if (strcmp(key, "luchtvochtigheid") == 0)   return "65";
    if (strcmp(key, "ventilatorsnelheid") == 0) return "1200";
    return "onbekend";
}

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
    bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    freeaddrinfo(result);
    listen(ListenSocket, SOMAXCONN);
    printf("Server luistert op poort %s...\n", DEFAULT_PORT);

    while (1) {
        SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) break;
        printf("Client verbonden!\n");

        char recvbuf[DEFAULT_BUFLEN];
        int iResult;
        do {
            iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN - 1, 0);
            if (iResult > 0) {
                recvbuf[iResult] = '\0';

                char key[DEFAULT_BUFLEN] = "";
                char sensorNaam[DEFAULT_BUFLEN] = "";
                sscanf(recvbuf, "%[^=]=%s", key, sensorNaam);
                printf("Ontvangen: %s\n", recvbuf);

                char antwoord[DEFAULT_BUFLEN];
                snprintf(antwoord, sizeof(antwoord), "%s=%s", sensorNaam, zoekWaarde(sensorNaam));
                send(ClientSocket, antwoord, (int)strlen(antwoord), 0);
                printf("Antwoord verstuurd: %s\n", antwoord);
            }
        } while (iResult > 0);

        printf("Client verbroken, wacht op nieuwe client...\n\n");
        closesocket(ClientSocket);
    }

    closesocket(ListenSocket);
    WSACleanup();
    return 0;
}