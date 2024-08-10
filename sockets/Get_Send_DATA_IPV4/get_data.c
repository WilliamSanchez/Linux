#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define BUF_SIZE 10
#define PORT_NUM 5501

struct controlData
{
    double rudder;
    double elevator;
    double aileron;
    double throttle;
}__attribute__((packed));

union temp64{
  int64_t ll;
  int32_t l[2];
};

void swap64(void *p)
{
     union temp64 *f, t;
     f = (union temp64 *)p;
     t.l[0] = htonl(f->l[1]);
     t.l[1] = htonl(f->l[0]);
     
     f->ll = t.ll;
}


/*	CLIENT		*/

char send_Data[32] = "Hola\n";

int main(int argc, char *argv[])
{
   struct sockaddr_in svaddr;
   int sfd, j;
   ssize_t numBytes;
   ssize_t msgLen;
   char resp[BUF_SIZE];

   
   sfd = socket(AF_INET, SOCK_DGRAM, 0);
   if(sfd == -1)
   {
   	perror("socket");
   }
   
   memset(&svaddr, 0, sizeof(struct sockaddr_in));
   svaddr.sin_family = AF_INET;
   svaddr.sin_addr.s_addr = INADDR_ANY;
   svaddr.sin_port = htons(PORT_NUM);
   
   struct controlData cdata;
      
   uint8_t cont = 0;
   
   for(;;)
   {
       //msgLen = strlen(send_Data);
       //if(sendto(sfd,send_Data, msgLen, 0, (struct sockaddr*)&svaddr, sizeof(struct sockaddr_in)) != msgLen)
      // {
        // perror("sendto");
      // }
       
      cdata.aileron = 2*cont/200 - 1;
      cdata.rudder = 2*cont/200 - 1;
      cdata.throttle = cont/200;
      cdata.elevator = 2*cont/200 - 1;
       
      swap64(&cdata.aileron);
      swap64(&cdata.rudder);
      swap64(&cdata.throttle);
      swap64(&cdata.elevator);
      
      if(sendto(sfd,&cdata,sizeof(cdata),0,(struct sockaddr *)&svaddr, sizeof(struct sockaddr_in)) != numBytes)
      	 perror("sendto");
      	 
      if(cont >= 200)
           cont = 0;
       cont++;
      /* 
       numBytes = recvfrom(sfd,resp,BUF_SIZE,0,NULL,NULL);
       if(numBytes == -1)
       {
          perror("recvfrom");
       }
       
       printf("Response: %.*s\n", (int)numBytes, resp);
      */ 
       usleep(500000);
   }
   exit(EXIT_SUCCESS);
}

