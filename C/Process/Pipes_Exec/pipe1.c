#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){

  int data_processed;
  int file_pipes[2];
  const char some_data[] = "123\n";
  char buffer[BUFSIZ +1];
  pid_t fork_result;
  
  memset(buffer,'\0',sizeof(buffer));
  
  if(pipe(file_pipes) == 0){
    
      fork_result = fork();
      if(fork_result == (pid_t)-1){
         fprintf(stderr,"Fork failure\n");
         exit(EXIT_FAILURE);
      }
      
      printf("%d fork = %d\n",getpid(),fork_result);
      
      if( fork_result == 0){
         printf("Child process \n");
         sprintf(buffer, "%d", file_pipes[0]);
         (void)execl("pipe2","pipe2",buffer,(char *)0);
         exit(EXIT_FAILURE);
      }else{
         data_processed = write(file_pipes[1],some_data,strlen(some_data));
         printf("%d - wrote %d bytes\n",getpid(), data_processed);      
      } 
  }
  exit(EXIT_SUCCESS);
}
