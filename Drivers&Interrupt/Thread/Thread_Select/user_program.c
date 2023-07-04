#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <assert.h>

int main(){

  char kernel_var[20];
  int fd,ret,n;
  fd_set read_fd, write_fd;
  struct timeval timeout;

  fd = open("/dev/William_device",O_RDWR | O_NONBLOCK);

  if(fd == -1){
    perror("open");
    exit(EXIT_FAILURE);
  }

  while(1){
 	puts("Starting select ....");

  	/*initialize the timeout*/
	FD_ZERO(&read_fd);
	FD_SET(fd,&read_fd);
	FD_ZERO(&write_fd);
	FD_SET(fd,&write_fd);

	/*Initizalize timeout*/
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	
	ret = select(FD_SETSIZE,&read_fd, &write_fd, NULL, &timeout);

	if(ret < 0){
	    perror("select");
	    assert(0);
	}  

	if(FD_ISSET(fd,&read_fd)){
	    read(fd,&kernel_var,sizeof(kernel_var));
	    printf("READ : kernel_val = %s\n", kernel_var);
	}

	if(FD_ISSET(fd,&write_fd)){
   	    strcpy(kernel_var,"User space");
	    write(fd,&kernel_var,strlen(kernel_var));
	    printf("WRITE : kernel_var = %s\n", kernel_var);
	}
  }
  //close(fd); 
}
