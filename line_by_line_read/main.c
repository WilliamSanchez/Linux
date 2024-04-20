/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

char data[256];

int main(void)
{

	
    int fd;
    
    fd = open("../canal_1.csv",O_RDONLY | O_NONBLOCK);
    if(fd == -1)
    	perror("Open file");
    
    if (lseek(fd,67,SEEK_SET) == -1)
    	perror("lseek");
    	
    
     read(fd,data,8);
     
     printf("=> 1 data read [%s]\n\r",data);
    
        if (lseek(fd,0,SEEK_CUR) == -1)
    	perror("lseek");
    	
    
     read(fd,data,8);
     
     printf("=> 2 data read [%s]\n\r",data);
    
    close(fd);
	
    printf("Close program \n\r");
    return 0;
}

