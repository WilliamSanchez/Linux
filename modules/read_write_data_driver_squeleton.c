#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
  int fd, len;
  char buff[64];
  
  if(argc < 0)
  {
  	printf();
  	return 0;
  }
  
  fd = open("/dev/nome_driver", O_RDWR);
  if(fd < 0)
  {
  	perror("open");
  	return fd;
  }
  
  write(fd, argv[1], strlen(argv[1]));
  
  printf("press enter to continue");
  getchar();	
  
  len = read(fd, buff, 64);
  printf("I got %d bytes %s\n", len, buff);
  
  close(fd);  
  return 0;
}
