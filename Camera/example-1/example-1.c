/*
  CODE created by kmdouglas
  
*/

#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

static const char DEVICE[] = "/dev/video0";

int print_capability(int fd)
{
  int ret;
  struct v4l2_capability caps = {0}; 
  
  ret = ioctl(fd,VIDIOC_QUERYCAP,&caps);
  if (ret == -1)
  {
      perror("Querying device capabilities");
      return errno;
  }
  
  printf("Driver caps\n\rDriver: %s\n\rCard: %s\n\rBus: %s\n\rVersion: %u.%u.%u\n\rCapabilities: %08x\n",caps.driver, \
  	caps.card, caps.bus_info,(caps.version>>16)&0xFF,(caps.version>>8)&0xFF, (caps.version)&0xFF, caps.capabilities);
  
  return 0;
  
}

int main()
{
   int fd;
   fd = open(DEVICE, O_RDWR);
   if(fd < 0)
   {
       perror(DEVICE);
       return errno;
   }
   
   print_capability(fd);
   
   close(fd);
   return 0;
}
