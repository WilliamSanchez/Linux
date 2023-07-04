#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
//#include <sys/wait.h>


int main(int argc, char *argv[]){
    
    int id = fork();
    int n;
    if( id == 0){
	n = 1;
        printf("child\n");
    }else{
	n = 6;
        printf("main\n");
    }

    if(id != 0){
//       wait(); 
    }
   

    int i;
    for(i=0; i<n+5; i++){
  	printf("%d ",i);
        fflush(stdout);
    }    

    if(id != 0){
       printf("\n");
    }

    
    return 0;
}
