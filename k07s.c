/*** UDP server program ***/
/* Usage: k07s <echo port> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 32

void excep(char *errMsg);
void clHandler(int serverSocket);

int main(int argc, char *argv[]) {
    int serverSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    unsigned short esPort;
    unsigned int clientLength;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    esPort = atoi(argv[1]);

    if ((serverSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        excep("socket() failed");
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(esPort);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        excep("bind() failed");
    }

    printf("UDP server listening on port %d...\n", esPort);

    clHandler(serverSocket);

    close(serverSocket);
    return 0;
}

void excep(char *errMsg) {
    perror(errMsg);
    exit(1);
}

void clHandler(int serverSocket) {
    struct sockaddr_in clientAddr;
    unsigned int clientLength;
    char buffer[BUFFER_SIZE];
    int byteRcvd;

    for (;;) {
        clientLength = sizeof(clientAddr);

        if ((byteRcvd = recvfrom(serverSocket, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&clientAddr, &clientLength)) < 0) {
            excep("recvfrom() failed");
        }

        printf("HANDLING CLIENT : %s\n", inet_ntoa(clientAddr.sin_addr));

		printf("RECEIVED MESSAGE : %s\n", buffer);

        if (sendto(serverSocket, buffer, byteRcvd, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) != byteRcvd) {
            excep("sendto() failed");
        }
    }
}

