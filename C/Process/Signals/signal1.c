#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ouch(int sig){

  printf("OUCH! -I got signal %d\n",sig);
  (void)signal(SIGINT,SIG_DFL);
}

int main(int argc, char *ragv[]){
 
   (void) signal(SIGINT,ouch);
   
   while(1){
     printf("Hello World!\n");
     sleep(1);
   }
   
   return 0;
}
