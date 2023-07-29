/*
  CODE created by kmdouglas
  
*/

#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

static const char DEVICE[] = "/dev/video0";

int request_buffers(int fd)
{
   struct v4l2_requestbuffers reqbuf;
   struct
   { 
	void *start;
	size_t length;   
   }*buffers;
   
   unsigned int i;
   
   memset(&reqbuf, 0, sizeof(reqbuf));
   reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   reqbuf.memory = V4L2_MEMORY_MMAP;
   reqbuf.count = 20;
   
   if(ioctl(fd, VIDIOC_REQBUFS, &reqbuf) == -1)
   {
   	if(errno == EINVAL)
   	{
   	   printf("Video capturing or mmap-streaming is not supported!\n");
   	}else{
   	   perror("VIDIOC_REQBUFS");
   	}
        exit(EXIT_FAILURE);
   }
   
   if(reqbuf.count < 5)
   {
      printf("Not enough buffer memeory\n");
      exit(EXIT_FAILURE);
   }
   
   buffers = calloc(reqbuf.count, sizeof(*buffers));
   assert(buffers != NULL);
   
   struct v4l2_buffer buffer;
   
   for(i=0; i< reqbuf.count; i++)
   {
      memset(&buffer, 0, sizeof(buffer));
      buffer.type = reqbuf.type;
      buffer.memory = V4L2_MEMORY_MMAP;
      buffer.index = i;
      
      if(ioctl(fd,VIDIOC_QUERYBUF, &buffer) == -1){
         perror("VIDIOC_QUERYBUF");
         exit(EXIT_FAILURE);
      }
      
      buffers[i].length = buffer.length;
      buffers[i].start = mmap(NULL,buffer.length, PROT_READ | PROT_WRITE, MAP_SHARED,fd,buffer.m.offset);
      
      if(MAP_FAILED == buffers[i].start)
      {
        perror("mmap");
        exit(EXIT_FAILURE);
      }
   }
   
   for(i=0; i< reqbuf.count; i++)
      munmap(buffers[i].start, buffers[i].length);
      
   free(buffers);
   
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
   
   request_buffers(fd);
   
   close(fd);
   return 0;
}
