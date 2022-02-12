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
  struct pollfd pfd;

  fd = open("/dev/William_device",O_RDWR | O_NONBLOCK);

  if(fd == -1){
    perror("open");
    exit(EXIT_FAILURE);
  }

  pfd.fd =fd;
  pfd.events = (POLLIN | POLLRDNORM | POLLOUT | POLLWRNORM);

  while(1){
 	puts("Starting poll ....");
 	ret = poll(&pfd,(unsigned long)1,5000);	// wait for 5 secs

	if(ret < 0){
	    perror("poll");
	    assert(0);
	}  

	if((pfd.revents & POLLIN) == POLLIN){
	    read(pfd.fd,&kernel_var,sizeof(kernel_var));
	    printf("POLLIN : kernel_val = %s\n", kernel_var);
	}

	if((pfd.revents & POLLOUT) == POLLOUT){
   	    strcpy(kernel_var,"User space");
	    write(pfd.fd,&kernel_var,strlen(kernel_var));
	    printf("POLLOUT : kernel_var = %s\n", kernel_var);
	}
  }
  //close(fd); 
}
