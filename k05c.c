/*** TCP/IP client program ***/
/* Usage: ./client HostName */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define PORT 50001
#define RCVBUFSIZE 32

char recvbuf[RCVBUFSIZE];

int main(int argc, char *argv[]) {
  struct sockaddr_in ServerAddr;
  struct hostent *HostInfo;
  int ClientSessionID;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: ./client HostName\n");
    exit(1);
  }
  
  if ((ClientSessionID = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "Failed to make a socket!\n");
    exit(1);
  }
  
  if ((HostInfo = gethostbyname(argv[1])) == NULL) {
    fprintf(stderr, "Failed to find host.\n");
    exit(1);
  }
  
  ServerAddr.sin_family = AF_INET;
  ServerAddr.sin_port = htons(PORT);
  memcpy((char *)&ServerAddr.sin_addr, (char *)HostInfo->h_addr_list[0], HostInfo->h_length);
  
  if (connect(ClientSessionID, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) == -1) {
    fprintf(stderr, "Failed to connect.\n");
    exit(1);
  }
  
  while (1) {
    if (recv(ClientSessionID, recvbuf, sizeof(recvbuf), 0) == -1) {
      fprintf(stderr, "Failed to recv a message.\n");
      exit(1);
    }
    
    printf("\nReceived message from server: %s\n", recvbuf);
    exit(1);
  }
  
  if (shutdown(ClientSessionID, 2) == -1) {
    fprintf(stderr, "Failed to shutdown.\n");
    exit(1);
  }
  
  close(ClientSessionID);
  
  return 0;
}
