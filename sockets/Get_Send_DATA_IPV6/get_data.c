#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUF_SIZE 10
#define PORT_NUM 5002

int main(int argc, char *argv[])
{
   struct sockaddr_in6 svaddr;
   int sfd, j;
   ssize_t numBytes;
   ssize_t msgLen;
   char resp[BUF_SIZE];
   
   if( argc < 3 || strcmp(argv[1],"--help") == 0)
   {
       perror("host-address msg");
   }
   
   sfd = socket(AF_INET6, SOCK_DGRAM, 0);
   if(sfd == -1)
   {
   	perror("socket");
   }
   
   memset(&svaddr, 0, sizeof(struct sockaddr_in6));
   svaddr.sin6_family = AF_INET6;
   svaddr.sin6_port = htons(PORT_NUM);
   
   if(inet_pton(AF_INET6, argv[1],&svaddr.sin6_addr) <= 0)
   {
     perror("inepton failed");
   }
   
   for(j=2; j< argc; j++)
   {
       msgLen = strlen(argv[j]);
       if(sendto(sfd,argv[j], msgLen, 0, (struct sockaddr*)&svaddr, sizeof(struct sockaddr_in6)) != msgLen)
       {
         perror("sendto");
       }
       
       numBytes = recvfrom(sfd,resp,BUF_SIZE,0,NULL,NULL);
       if(numBytes == -1)
       {
          perror("recvfrom");
       }
       
       printf("Response %d: %.*s\n", j-1, (int)numBytes, resp);
   }
   exit(EXIT_SUCCESS);
}

