#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 10
#define PORT_NUM 5002

int main()
{
   struct sockaddr_in6 svaddr, claddr;
   int sfd, j;
   ssize_t numBytes;
   socklen_t len;
   char buf[BUF_SIZE];
   char claddrStr[INET6_ADDRSTRLEN];
   
   sfd = socket(AF_INET6, SOCK_DGRAM, 0);
   if(sfd == -1)
   {
   	perror("socket");
   }
   
   memset(&svaddr, 0, sizeof(struct sockaddr_in6));
   svaddr.sin6_family = AF_INET6;
   svaddr.sin6_addr = in6addr_any;
   svaddr.sin6_port = htons(PORT_NUM);
   
   if(bind(sfd,(struct sockaddr *)&svaddr,sizeof(struct sockaddr_in6)) == -1)
   {
      perror("Bind");
   }


   while(1)
   {
      len = sizeof(struct sockaddr_in6);
      
      numBytes = recvfrom(sfd,buf,BUF_SIZE,0,(struct sockaddr*)&claddr,&len);
      if(numBytes == -1)
      {
      	 perror("recvfrom");
      }
      
      if(inet_ntop(AF_INET6,&claddr.sin6_addr,claddrStr,INET6_ADDRSTRLEN) == NULL)
      {
        printf("Couldn't convert client address to string \n");
      }else{
        printf("Server received %ld bytes from (%s,%u)\n",(long)numBytes,claddrStr, ntohs(claddr.sin6_port));
      }
      
      for(j=0; j < numBytes; j++)
      {
           buf[j] = toupper((unsigned char)buf[j]);
      }
      
      if(sendto(sfd,buf,numBytes,0,(struct sockaddr *)&claddr,len) != numBytes)
         perror("sendto");
   
   }

   return 0;
}

