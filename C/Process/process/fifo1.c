#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "myFifo1"

int main(int argc, char *argv[]){

   int res;
   int open_mode = 0;
   int i;
   
   if(argc < 2){
      fprintf(stderr,"Usage: %s <some combination of O_RDONLY OWRONLY O_NONBLOCK>\n",*argv);
      exit(EXIT_FAILURE);
   }
   
   for(i=1; i<argc; i++){
      if(strncmp(*++argv,"O_RDONLY",8) == 0)
          open_mode |= O_RDONLY;
      if(strncmp(*argv,"O_WRONLY",8) == 0)
          open_mode |= O_WRONLY;
      if(strncmp(*argv, "O_NONBLOCK", 10) == 0)
          open_mode |= O_NONBLOCK;   
   }
   
   if(access(FIFO_NAME, F_OK) == -1){
      res = mkfifo(FIFO_NAME, 0777);
      if(res != 0){
         fprintf(stderr,"Could not create fifo %s\n",FIFO_NAME);
         exit(EXIT_FAILURE);
      }
   }
   
   printf("Process %d opening FIFO\n",getpid());
   res = open(FIFO_NAME,open_mode);
   printf("Process %d resutl %d\n",getpid(),res);
   sleep(5);
   if(res != -1)(void)close(res);
   printf("Process %d finished\n",getpid());
   exit(EXIT_SUCCESS); 
}
