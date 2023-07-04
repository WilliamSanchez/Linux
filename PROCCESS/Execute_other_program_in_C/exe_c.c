#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "Hello William";
    char buffer[BUFSIZ+1];
    pid_t fork_result; 
    
    memset(buffer,'\0',sizeof(buffer));
    printf("Main, this is my ID: %d\n", getpid());
    
    if(pipe(file_pipes) == 0){
	fork_result = fork();
        if(fork_result == (pid_t)-1){
	     fprintf(stderr,"Fork failure");
	     exit(EXIT_FAILURE);
        }
   
        if(fork_result == 0){
	  sprintf(buffer,"%d",file_pipes[0]);
          (void)execl("pipe4","pipe4",buffer,(char*)0);
	  exit(EXIT_FAILURE);
        }else{
          sleep(1);
          data_processed = write(file_pipes[1],some_data,strlen(some_data));
          printf("%d -> wrote %d bytes\n",getpid(),data_processed);     
        }  	
    }

    exit(EXIT_SUCCESS);
}
