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
  struct v4l2_cropcap cropcaps = {0}; 
  
  cropcaps.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  ret = ioctl(fd,VIDIOC_CROPCAP,&cropcaps);
  if (ret == -1)
  {
      perror("Querying device crop capabilites");
      return errno;
  }
  
  printf("Camera Cropping\n\rBound: %dx%d+%d+%d\n\rDefault: %dx%d+%d+%d\n\rAspect: %d/%d\n", \
  	cropcaps.bounds.width,cropcaps.bounds.height,cropcaps.bounds.left,cropcaps.bounds.top, \
  	cropcaps.defrect.width, cropcaps.defrect.height,cropcaps.defrect.left,cropcaps.defrect.top, \
  	cropcaps.pixelaspect.numerator,cropcaps.pixelaspect.denominator);
  
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
