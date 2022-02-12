#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <assert.h>

#define EPOLL_SIZE	(256)
#define MAX_EVENTS	(20)

int main(){

  char kernel_var[20];
  int fd,ret,n, epoll_fd;
  struct epoll_event ev, events[20];

  fd = open("/dev/William_device",O_RDWR | O_NONBLOCK);

  if(fd == -1){
    perror("open");
    exit(EXIT_FAILURE);
  }

  //create epoll instance
  epoll_fd = epoll_create(EPOLL_SIZE);

  if(epoll_fd == -1){
    perror("open");
    exit(EXIT_FAILURE);
  }

  ev.data.fd = fd;
  ev.events = (EPOLLIN| EPOLLOUT);

  //Add the fd to the epoll
  if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD,fd,&ev)){
    perror("Failed to add file descriptor to epoll\n");
    close(epoll_fd);
    exit(EXIT_FAILURE);
  }

  while(1){
 	puts("Starting poll ....");
	ret = epoll_wait(epoll_fd,events,MAX_EVENTS,5000);

	if(ret < 0){
	    perror("epoll_wait");
	    close(epoll_fd);
	    assert(0);
	}  

	for(n=0; n<ret; n++){

	    if((events[n].events & EPOLLIN)==EPOLLIN){
	      read(events[n].data.fd,&kernel_var,sizeof(kernel_var));
	      printf("EPOLLIN : kernel_val = %s\n", kernel_var);
	    }

	    if((events[n].events & EPOLLOUT)==EPOLLOUT){
   	      strcpy(kernel_var,"User space");
	      write(events[n].data.fd,&kernel_var,strlen(kernel_var));
	      printf("WRITE : kernel_var = %s\n", kernel_var);
	    }
	}
  }
  if(close(epoll_fd)){
      perror("Failed to close epoll file descriptor\n");
  }
  if(close(fd)){
      perror("Failed to close file descriptor\n");
  };
  return 0; 
}
