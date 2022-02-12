#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WR_VALUE _IOW('a','b',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int main(){

  int fd;
  int32_t value, number;
  printf("*********************************\n");
  printf("****   William Sanchez    *******\n");
  
  fd = open("/dev/William_device",O_RDWR);
  if(fd < 0){
	printf("Cannot ope device file ..\n");
	return 0;
  }
  printf("Enter the value to send\n");
  scanf("%d",&number);
  printf("Writting value to Driver\n");
  ioctl(fd,WR_VALUE,(int32_t*) &number);

  printf("Reading value from Driver\n");
  ioctl(fd,RD_VALUE,(int32_t*) &value);
  printf("value is %d\n",value);

  printf("close Driver\n");
  close(fd); 
}
