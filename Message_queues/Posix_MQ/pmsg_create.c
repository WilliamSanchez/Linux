#include <stdio.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>

#define GN_ANY_BASE   0100      /* Can use any base - like strtol(3) */
#define GN_BASE_8     0200      /* Value is expressed in octal */
#define GN_BASE_16    0400      /* Value is expressed in hexadecimal */

static void usageError(const char *progName)
{
  fprintf(stderr, "Usage: %s [-cx] [-m maxmsg] [-s sgsize] mq-name "
  		"[octals-perms]\n",progName);
  fprintf(stderr,"	-c	    Create queue (O_CREAT)\n");
  fprintf(stderr,"	-m maxmsg   Set maximum # of messages\n");
  fprintf(stderr,"	-s msgsize  Set maximum message size\n");
  fprintf(stderr,"	-x	    Create exclusively (O_EXCL)\n");
  
}


int main(int argc, char *argv[])
{
   int flags, opt;
   mode_t perms;
   mqd_t mqd;
   struct mq_attr attr, *attrp;
   
   attrp=NULL;
   attr.mq_maxmsg = 10;
   attr.mq_msgsize = 2048;
   flags = O_RDWR;

   while((opt = getopt(argc, argv, "cm:s:x")) != -1)
   {
      switch(opt)
      {
        case 'c':
            flags |= O_CREAT;
            break;
            
        case 'm':
            attr.mq_maxmsg = atoi(optarg);
            attrp=&attr;
            //printf("optarg> %d\n",atoi(optarg));
            break;
            
        case 's':
            attr.mq_msgsize = atoi(optarg);
            attrp=&attr;
            break;
            
        case 'x':
            flags |= O_EXCL;
            break;
            
        default:
            usageError(argv[0]);
      }   
   }
   
   if(optind >= argc)
   	usageError(argv[0]);
   
//   perms = (argc <= optind+1) ? (S_IRUSR | S_IWUSR) : getInt(argv[optind+1],GN_BASE_8,"octal-perms");
   perms = (argc <= optind+1) ? (S_IRUSR | S_IWUSR) :  (S_IRWXU);
   
   mqd = mq_open(argv[optind], flags, perms, attrp);
   
   if(mqd == (mqd_t) -1)
     perror("mq_open");
     
   exit(EXIT_SUCCESS);
   
   return 0;
}

