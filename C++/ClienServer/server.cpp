#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE_1 "/tmp/client2server_fifo"
#define FIFO_FILE_2 "/tmp/server2client_fifo"

#define BUF_SIZE 1024

int main()
{

   int client_to_server;
   int server_to_client;
   
   char buf[BUFSIZ];
   
   mkfifo(FIFO_FILE_1,0777);
   mkfifo(FIFO_FILE_2,0777);
   
   printf("Server ON.\n\r");   
   
  while(1)
   {
       client_to_server = open(FIFO_FILE_1,O_RDONLY);
       server_to_client = open(FIFO_FILE_2,O_WRONLY);
       
       read(client_to_server,buf,BUFSIZ);
       
       if(strcmp("exit",buf) == 0)
       {
          printf("Server OFF.\n");
          break;
       }
       else if(strcmp("",buf) != 0)
       {
             printf("Received: %s\n",buf);
             printf("Sending back ...\n");
             write(server_to_client,buf,BUFSIZ);  
             break;      
       }
       
        memset(buf,0,sizeof(buf));
               
   }
          
   close(client_to_server);
   close(server_to_client); 
   
   unlink(FIFO_FILE_1);
   unlink(FIFO_FILE_2);
   return 0;
}
