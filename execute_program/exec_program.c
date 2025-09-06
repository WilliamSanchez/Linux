#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main(){
    
    char *some_data1[] = {"/bin/ls", "-l", NULL};
    char *some_data2[] = {"/usr/bin/echo","Sanchez",NULL};
    char *some_data3[] = {"/usr/bin/echo","William Sanchez Farfan",NULL};
    
    printf("Initial value of USER: %s\n", getenv("USER"));
    if(putenv("USER=William")!=0)
    	perror("putenv");
 
    int id = fork();
     if( id == 0){
        printf("child\n");
        if(execv(some_data3[0],some_data3) == -1)
    		perror("execv failed");
    	exit(EXIT_SUCCESS);
    }else{
        printf("main\n");
        //sleep(5);
        //wait(NULL);
    }
    
    printf("Parent\n");
    wait(NULL);
    
    //execl("/usr/bin/printenv","printenv","USER","SHELL",(char*)NULL);
    //execv(some_data1[0],some_data1);
    //execv(some_data2[0],some_data2);
    /*
    if(execv(some_data3[0],some_data3) == -1)
    	perror("execv failed");
    exit(EXIT_SUCCESS);
    */
    exit(EXIT_SUCCESS);
}
