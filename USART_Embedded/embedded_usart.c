#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>


int main(int argc, char *argv[]){

  int file, count;

  if(argc != 2){
     printf("Invalid number of arguments, existing!\n");
     return -2;
  }
  
  if(file = open("/dev/ttyO4",O_RDWR | O_NOCTTY | O_NDELAY) < 0){
      perror("UART: Failed to open the file.\n");
      return -1;
  }

  struct termios options;
  tcgetattr(file,&options);

  options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
  options.c_iflag = IGNPAR | ICRNL;
  tcflush(file,TCIFLUSH);
  tcsetattr(file,TCSANOW,&options);
  
  if((count = write(file,argv[1],strlen(argv[1])+1)) < 0){
    perror("Failed to write to the output\n");
    return -1;
  }
  usleep(10000);
  
  unsigned char receive[100];
  if((count = read(file,(void*)receive,100)) < 0){
    perror("Failed to read from input\n");
    return -1;    
  }
  
  if(count == 0){
    printf("There was no data available to read!\n");
  }else{
    receive[count]=0;
    printf("The following was read in [%d]: %s\n",count,receive);
  }
  close(file);
  return 0;
}
