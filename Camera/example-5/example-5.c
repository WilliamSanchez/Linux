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
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

static const char DEVICE[] = "/dev/video0";

int fd;
struct
{ 
   void *start;
   size_t length;   
}*buffers;

unsigned int num_buffers;
struct v4l2_requestbuffers reqbuf = {0};

/**
	Wrapper around ioctl calls.
**/

static int xioctl(int fd, int request, void *arg)
{
   int r;
   do
   {
       r = ioctl(fd, request, arg);
   }while(EINTR == errno && r == -1);
   
   return r;
}


 static void init_mmap(void)
 {
   reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   reqbuf.memory = V4L2_MEMORY_MMAP;
   reqbuf.count = 5;
   
   if(xioctl(fd, VIDIOC_REQBUFS, &reqbuf) == -1)
   {
     perror("VIDIOC_TREQBUFS");
     exit(errno);
   }
   
   if(reqbuf.count < 2)
   {
       printf("Not enough buffer memory\n");
       exit(EXIT_FAILURE);
   }
   
   buffers = calloc(reqbuf.count, sizeof(*buffers));
   assert(buffers != NULL);
   
   num_buffers = reqbuf.count;
   
   // create the buffer memory mmaps
   struct v4l2_buffer buffer;   
   for(unsigned int i=0; i< reqbuf.count; i++)
   {
      memset(&buffer, 0, sizeof(buffer));
      buffer.type = reqbuf.type;
      buffer.memory = V4L2_MEMORY_MMAP;
      buffer.index = i;
      
      if(xioctl(fd,VIDIOC_QUERYBUF, &buffer) == -1){
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
 }
 
 static void init_device()
 {
    struct v4l2_fmtdesc fmtdesc = {0}; 
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    
    while(0 == xioctl(fd,VIDIOC_ENUM_FMT,&fmtdesc))
    {
      fmtdesc.index++;
    }
    
    printf("\nUsing format: %s\n",fmtdesc.description);
    
    struct v4l2_format fmt={0};
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 640;
    fmt.fmt.pix.height = 480;
    fmt.fmt.pix.pixelformat = fmtdesc.pixelformat;
    fmt.fmt.pix.field = V4L2_FIELD_NONE;
    
    if(xioctl(fd,VIDIOC_S_FMT,&fmt) == -1)
    {
      perror("VIDIOC_S_FMT");
      exit(errno);
    }
    
    char format_code[5];
    strncpy(format_code,(char*)&fmt.fmt.pix.pixelformat,5);
  
    printf("Set format\n\rWidth: %d\n\rHeight: %d\n\rPixel Format: %s\n\rField: %d\n", \
    fmt.fmt.pix.width, fmt.fmt.pix.height, format_code, fmt.fmt.pix.field);
    
    init_mmap();
 }
 
 static void start_capturing(void)
 {
    enum v4l2_buf_type type;
    
    struct v4l2_buffer buffer;
    for(unsigned int i = 0; i<num_buffers; i++)
    {
        memset(&buffer, 0, sizeof(buffer));
        buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buffer.memory = V4L2_MEMORY_MMAP;
        buffer.index = i;
        
        // enqueue the buffer with VIDIOC_QBUF
        if(xioctl(fd,VIDIOC_QBUF, &buffer) == -1)
        {
            perror("VIDIOC_QBUF");
            exit(errno);
        }
    }
    
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    
    if(xioctl(fd,VIDIOC_STREAMON, &type) == -1)
    {
         perror("VIDIOC_STREAMON");
         exit(errno);
    }
 }
 
 static void stop_capturing(void)
 {
   enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   if(xioctl(fd,VIDIOC_STREAMOFF, &type) == -1)
   {
         perror("VIDIOC_STREAMOFF");
         exit(errno);
   }
   
 }
 
 static void process_image(const void *pBuffer)
 {
     fputc('.',stdout);
     fflush(stdout);
 }
 
 static int read_frame(void)
 {
     struct v4l2_buffer buffer;
     memset(&buffer, 0, sizeof(buffer));
     buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
     buffer.memory = V4L2_MEMORY_MMAP;
     
     //Dequeue a buffer
     if(xioctl(fd, VIDIOC_DQBUF, &buffer) == -1)
     {
       switch(errno)
       {
          case EAGAIN:
               return 0;
          case EIO:
          
          default:
              perror("VIDIOC_QBUF");
              exit(errno);
       }
     }
     
     assert(buffer.index < num_buffers);
     
     process_image(buffers[buffer.index].start);
     
     //Enqueue the buffer again
     if(xioctl(fd, VIDIOC_QBUF, &buffer) == -1)
     {
         perror("VIDIOC_QBUF");
         exit(errno);
     }
     
     return 1;
 }
 
 static void main_loop(void)
 {
    unsigned int count = 100;
    while(count-- > 0)
    {
      fd_set fds;
      struct timeval tv;
      
      int r;
      for(;;)
      {
          FD_ZERO(&fds);
          FD_SET(fd, &fds);
          
          tv.tv_sec = 2;
          tv.tv_usec = 0;
          
          r = select(fd +1, &fds, NULL, NULL, &tv);
          if(r == -1)
          {
              if(EINTR == errno)
                continue;
                
              perror("select");
              exit(errno);
          }
          
          if(r == 0)
          {
             fprintf(stderr,"select timeout\n");
             exit(EXIT_FAILURE);
          }
          
          if(read_frame())
            break;
      }
    }
 }
 

int main()
{

   fd = open(DEVICE, O_RDWR);
   if(fd < 0)
   {
       perror(DEVICE);
       return errno;
   }
   
   init_device();
   
   start_capturing();
   
   main_loop();
   
   stop_capturing();
   
   for(unsigned int i=0; i< reqbuf.count; i++)
   {
      munmap(buffers[i].start, buffers[i].length);
   }
   
   free(buffers);
   close(fd);
   
   printf("\n\nDone.\n");
   return 0;
}

