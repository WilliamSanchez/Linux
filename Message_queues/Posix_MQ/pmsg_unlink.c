#include <mqueue.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
   if(argc != 2 || strcmp(argv[1], "--help") == 0)
	perror("mq-name"); 
	
   if(mq_unlink(argv[1]) == -1)
     perror("mq_unlink");	
	
   exit(EXIT_SUCCESS); 
}
