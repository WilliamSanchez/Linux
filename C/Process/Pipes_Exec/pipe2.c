#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

   /*
      argv[0], Which takes the program name
      argv[1], Which contains the file descriptor number you want  the program to read from 
      (char*)0, Which terminates the parameter
   */
  
  int data_processed;
  char buffer[BUFSIZ+1];
  int file_descriptor;
  
  memset(buffer,'\0',sizeof(buffer)); 
  sscanf(argv[1],"%d", &file_descriptor);
  data_processed = read(file_descriptor, buffer, BUFSIZ);

  printf("\n%d - read %d bytes: %s",getpid(), data_processed, buffer);
  exit(EXIT_SUCCESS);
}
