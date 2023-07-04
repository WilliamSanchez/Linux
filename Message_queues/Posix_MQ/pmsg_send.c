#include <mqueue.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

static void usageError(char *progName)
{
  fprintf(stderr,"Usage: %s[-n] name msg [prio]\n",progName);
  fprintf(stderr,"  -n  Use O_NONBLOCK flag\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  int flags,opt;
  mqd_t mqd;
  unsigned int prio;
  
  flags = O_WRONLY;
  while((opt = getopt(argc, argv, "n")) != -1)
  {
     switch(opt)
     {
        case 'n': flags |= O_NONBLOCK; break;
        default: usageError(argv[0]);
     }
  }

  if(optind + 1 >= argc)
     usageError(argv[0]);

  mqd = mq_open(argv[optind],flags);
  
  if(mqd == (mqd_t)-1)
     perror("mq_open");
    
  prio = (argc > optind +2) ? atoi(argv[optind+2]) : 0;  
    
  if(mq_send(mqd, argv[optind+1],strlen(argv[optind+1]),prio) == -1)
     perror("mq_send");  
  
  exit(EXIT_SUCCESS);
}
