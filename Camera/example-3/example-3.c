/*
  CODE created by kmdouglas
  
*/

#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

static const char DEVICE[] = "/dev/video0";

int print_and_set_format(int fd)
{
  
  struct v4l2_fmtdesc fmtdesc = {0}; 
  fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  
  char c, e;
  while(0 == ioctl(fd,VIDIOC_ENUM_FMT,&fmtdesc))
  {
      c = fmtdesc.flags & 1 ? 'C':' ';
      e = fmtdesc.flags & 2 ? 'E':' '; 
      
      printf("%c%c %s\n", c, e, fmtdesc.description);
      fmtdesc.index++;
  }
  
  printf("\nUsing format: %s\n",fmtdesc.description);
  
  struct v4l2_format fmt={0};
  
  fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  fmt.fmt.pix.width = 320;
  fmt.fmt.pix.height = 240;
  fmt.fmt.pix.pixelformat = fmtdesc.pixelformat;
  fmt.fmt.pix.field = V4L2_FIELD_NONE;
  
  if(ioctl(fd,VIDIOC_S_FMT,&fmt) == -1)
  {
    perror("Could not set format description");
    return -1;
  }
  
  char format_code[5];
  strncpy(format_code,(char*)&fmt.fmt.pix.pixelformat,5);
  
  printf("Set format\n\rWidth: %d\n\rHeight: %d\n\rPixel Format: %s\n\rField: %d\n", \
  	fmt.fmt.pix.width, fmt.fmt.pix.height, format_code, fmt.fmt.pix.field);
  
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
   
   print_and_set_format(fd);
   
   close(fd);
   return 0;
}
