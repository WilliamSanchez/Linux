#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigtstop(){
   printf("Stop not allowed\n");
}

int main(int argc, char *argv[]){
    
    signal(SIGTSTP,&handle_sigtstop);

    int x;
    printf("Input number: ");
    scanf("%d",&x);
    printf("Result %d * 5 = %d\n",x,x*5);    

    exit(EXIT_SUCCESS);
}
