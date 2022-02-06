#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
 
   int pid = fork();
   if(pid == -1){
      return 1;
   }
   
   if(pid == 0){
     
      int file=open("pingResult.txt",O_WRONLY | O_CREAT, 0777);
      if(file == -1){
          printf("Not open the file\n");
          return 2;
      }
      printf("The fd to pingResult: %d\n",file);
      dup2(file,STDOUT_FILENO);
      close(file);

      int err=execlp("ping","ping","-c","3","google.com",NULL);
      if(err == -1){
         printf("Could not find progra to execute or other error ocurred\n");
         return 2;
      }   
   }else{
     int wstatus;
     wait(&wstatus);
     
     if(WIFEXITED(wstatus)){
        int statusCode = WEXITSTATUS(wstatus);
        if(statusCode == 0){
           printf("Success\n");
        }else{
           printf("Failured with status code %d\n",statusCode);
        }
     }
   
   
   }

   return 0;
}
