#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    int data_processed;
    int file_pipes[2];
    const char some_data[]="Hello William, this is a pipe";
    char buffer[BUFSIZ+1];    
    pid_t fork_result;

    memset(buffer,'\0',sizeof(buffer));

    if(pipe(file_pipes) == 0){
        
        fork_result = fork();

	if(fork_result == -1){
	    fprintf(stderr,"Fork Failure");
            exit(EXIT_FAILURE);
       	}

	if(fork_result == 0){
	   data_processed = read(file_pipes[0],buffer,BUFSIZ);
	   printf("I am in the child process, Read %d bytes: [%s]\n",data_processed,buffer);
	   exit(EXIT_SUCCESS);
        }else{
	   data_processed = write(file_pipes[1],some_data,strlen(some_data));
	   printf("I am in the parent process, wrote %d\n",data_processed);sleep(1);
           exit(EXIT_SUCCESS);
  	}

    }
    exit(EXIT_SUCCESS);
}
