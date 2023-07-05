#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>


#define FIFO_FILE_1 "/tmp/client2server_fifo"
#define FIFO_FILE_2 "/tmp/server2client_fifo"

int main()
{
   system("clear");
   int client_to_server;
   int server_to_client;
   
   char str[140];
   
   printf("Input message to server: ");
   scanf("%139[^\r\n]",str);
   
   client_to_server = open(FIFO_FILE_1,O_WRONLY);
   server_to_client = open(FIFO_FILE_2,O_RDONLY);
   
   if(write(client_to_server, str, sizeof(str)) < 0)
   {
        perror("Write:");
        exit(-1);   
   }
   
 sleep(10);
   if(read(server_to_client, str, sizeof(str)) < 0)
   {
   	perror("Read");
   	exit(-1);
   }
   

   printf("\n ... received from the server: %s\n\n\n",str);

   close(client_to_server);
   close(server_to_client);   
        
  return 0;
}

