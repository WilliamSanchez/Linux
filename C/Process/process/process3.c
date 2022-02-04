#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

   pid_t pid;
   char *message;
   int n;
   
   printf("fork program starting\n");
   pid = fork();
   switch(pid){
     case -1:
         perror("fork failed!");
         exit(1);
     case  0:
         message = "This is the child";
         //printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
         n=5;
         break;
     default:
         message = "This is the parent";
         //printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
         n=3;
         break;   
   }
   
   for(; n>0; n--){
       puts(message);
       printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
       sleep(1);
   }
   
   

   exit(0);
}
