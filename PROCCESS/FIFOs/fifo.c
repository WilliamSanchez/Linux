#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    
    int res = mkfifo("myfifo1",0777);
    if(res == -1){

	if(errno != EEXIST){
   	  printf("Could not created fifo file\n");
          return 1;
 	}
    }
    printf("Opening ...\n");
    int fd = open("myfifo1",O_WRONLY);
    printf("Opened ...\n");
    int x = 97;
    if(write(fd,&x,sizeof(x)) == -1){
	return 2;
    }

    printf("Written ...\n");
    close(fd);   
    printf("Closed ...\n");  

    exit(EXIT_SUCCESS);
}
