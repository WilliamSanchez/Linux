#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define FIFO_NAME "sum"

int main(int argc, char *ragv[]){

   int arr[5];
   srand(time(NULL));
   int i;
   
   for(i=0; i<5; i++){
     arr[i] = rand()%100;
     printf("Generated %d\n",arr[i]);
   }
   
   //NOTE: you will have to create the fifo uing the command "mkfifo sum"
   int res;
   if(access(FIFO_NAME, F_OK) == -1){
      res = mkfifo(FIFO_NAME, 0777);
      if(res != 0){
         fprintf(stderr,"Could not create fifo %s\n",FIFO_NAME);
         exit(EXIT_FAILURE);
      }
   }
   
   int fd = open(FIFO_NAME,O_WRONLY);
   if(fd == -1){
     return 1;
   }
   
   if(write(fd, arr,sizeof(int)*5) == -1){
      return 2;
   }
   
   close(fd);
   
   return 0;
}
