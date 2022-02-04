#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[]){

  int p1[2];
  int p2[2];
  
  if(pipe(p1) == -1){
    fprintf(stderr,"Could not create fifo\n");
    return 1; 
  }

   if(pipe(p2) == -1){
     fprintf(stderr,"Could not create fifo \n");
     return 2;
   }
   
   int pid = fork();
   if(pid == -1){
      fprintf(stderr,"Could not create process\n");
      return 3;
   }
   
   if(pid == 0){
      
        // child process
      close(p1[0]);
      close(p2[1]);
      
      int x;
      if(read(p2[0], &x, sizeof(int)) == -1){
         fprintf(stderr,"Could not read the file\n");
         return 3;     
      }  
      
      printf("Child process: Received %d\n",x);
      
      x *= 4;
      
      if(write(p1[1], &x, sizeof(int)) == -1){
         fprintf(stderr,"Could not write the file\n");
         return 4;
      }
      
      printf("Child process Wrote %d\n",x);
      close(p1[1]);
      close(p2[0]);
   }else{
     
     // Parent process
     close(p1[1]);
     close(p2[0]);
     
     srand(time(NULL));
     int y = rand()%10;
     
     if(write(p2[1], &y, sizeof(y)) == -1){
         fprintf(stderr,"Could not write the file\n");
         return 5;
     }
     
     printf("Parent process: Wrote %d\n",y);
     
     if(read(p1[0],&y,sizeof(y)) == -1){
        fprintf(stderr,"Could not read the file\n");
        return 6;
     }
     
     printf("Parent process: Result is %d\n",y);
     close(p1[0]);
     close(p2[1]);
     wait(NULL);   
   }
   
   
   
   
  return 0;
}
