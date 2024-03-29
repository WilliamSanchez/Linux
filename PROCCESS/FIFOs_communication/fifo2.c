#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

#define FIFO_NAME 	"myFifo1"
#define BUFFER_SIZE 	PIPE_BUF

#define TEN_MEG		(1024 * 1024 * 10)

int main(int argc, char *argv[]){

    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    int bytes_read = 0;
    char buffer[BUFFER_SIZE+1];
   
    memset(buffer,'\0',sizeof(buffer));

    printf("Process %d opening FIFO O_RDONLY\n",getpid());
    pipe_fd = open(FIFO_NAME,open_mode);
    printf("Process %d result %d\n",getpid(),pipe_fd);

    if(pipe_fd != -1){
	do{
	     res = read(pipe_fd,buffer,BUFFER_SIZE);
	     bytes_read += res;
 	}while(res > 0);

    }else{
	exit(EXIT_FAILURE);
    }

    printf("Process %d finished, %d bytes read\n",getpid(),bytes_read);
    exit(EXIT_SUCCESS);
}
