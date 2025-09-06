#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_CMD_LEN	200 

/*

The return value of system() is one of the following:

       •  If command is NULL, then a nonzero value if a shell is available, or 0 if no shell is available.

       •  If a child process could not be created, or its status could not be retrieved, the return value  is
          -1 and errno is set to indicate the error.

       •  If a shell could not be executed in the child process, then the return value is as though the child
          shell terminated by calling _exit(2) with the status 127.

       •  If  all  system  calls  succeed, then the return value is the termination status of the child shell
          used to execute command.  (The termination status of a shell is the termination status of the  last
          command it executes.)


*/

int main(int argc, char *argv[]){
        
    char str[MAX_CMD_LEN];
    int status;
    
    for(;;)
    {
    	printf("Command: ");
    	fflush(stdout);
    	if(fgets(str, MAX_CMD_LEN, stdin) == NULL)
    		break;
    	
    	status = system(str);
    	printf("system() returned: status=0x%04x (%d,%d)\n",(unsigned int) status, status>>8, status &0xff); 
    }
    
    return 0;
}
