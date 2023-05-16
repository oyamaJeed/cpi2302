/*** TCP/IP server program ***/
/* Usage: k06s <echo port> */

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
#define MAXPENDING 5

void excep(char *errMsg);
void clHandler(int clSock);

int main(int argc, char *argv[]) {
  int serverSocket;
  int clientSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_in clientAddr;
  unsigned short esPort;
  unsigned int clientLength;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);
  }

  esPort = atoi(argv[1]);

  if ((serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    excep("socket() failed");
  }

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(esPort);

  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    excep("bind() failed");
  }

  if (listen(serverSocket, MAXPENDING) < 0) {
    excep("listen() failed");
  }

  printf("Waiting for incoming connections...\n");

  for (;;) {
    clientLength = sizeof(clientAddr);

    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLength)) < 0) {
      excep("accept() failed");
    }

    printf("CONNECTED CLIENT: %s\n", inet_ntoa(clientAddr.sin_addr));

    clHandler(clientSocket);
  }
}

void excep(char *errMsg) {
  perror(errMsg);
  exit(1);
}

void clHandler(int clSock)
{
  char buffer[BUFFER_SIZE];
  int recvMsgSize;

  if((recvMsgSize = recv(clSock, buffer, BUFFER_SIZE, 0)) < 0){
    excep("recv() failed");
  }

  while(recvMsgSize > 0)
  {
    if (send(clSock, buffer, recvMsgSize, 0) != recvMsgSize) {
      excep("send() failed");
    }

    if((recvMsgSize = recv(clSock, buffer, BUFFER_SIZE, 0)) < 0){
      excep("recv() failed");
    }
  }
  close(clSock);
}
