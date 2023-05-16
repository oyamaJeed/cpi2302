/*** TCP/IP client program ***/
/* Usage: k06c <server IP> <echo word> [<echo port>] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define BUFFER_SIZE 32

void excep(char *errMsg);

int main(int argc, char *argv[]) {
  struct sockaddr_in ServerAddr;
  struct hostent *HostInfo;
  int ClientSessionID;
  char buffer[BUFFER_SIZE];
  unsigned short esPORT;
  int totalBytesRcvd;
  int byteRcvd;

  if ((argc < 3) || (argc >4)) {
    fprintf(stderr, "Usage: %s <ServerIP> <Echo Word> [<Echo Port>]\n", argv[0]);
    exit(1);
  }
  
  char* serverIP = argv[1];
  char* message = argv[2];
  
  if(argc == 4){
    esPORT = atoi(argv[3]);
  }else{
    esPORT = 7;
  }

  if ((ClientSessionID = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    excep("socket() failed");
  }

  if ((HostInfo = gethostbyname(argv[1])) == NULL) {
    excep("Failed to find host.\n");
  }
  
  ServerAddr.sin_family = AF_INET;
  ServerAddr.sin_port = htons(esPORT);
  memcpy((char *)&ServerAddr.sin_addr, (char *)HostInfo->h_addr_list[0], HostInfo->h_length);
  
  if (connect(ClientSessionID, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) < 0) {
    excep("connect() failed");
  }
  
  if (send(ClientSessionID, message, strlen(message), 0) != strlen(message)) {
    excep("send() failed");
  }
  
  totalBytesRcvd = 0;
  printf("RECEIVED MESSAGE: ");

  while(totalBytesRcvd < strlen(message))
  {
    if((byteRcvd = recv(ClientSessionID, buffer, BUFFER_SIZE - 1, 0)) <= 0){
      excep("recv() failed or connection closed prematurely");
    }
    totalBytesRcvd += byteRcvd;
    buffer[byteRcvd] = '\0';
    printf("%s",buffer);
  }

  printf("\n");
  
  close(ClientSessionID);
  exit(0);
}

void excep(char *errMsg)
{
	perror(errMsg);
	exit(1);
}

