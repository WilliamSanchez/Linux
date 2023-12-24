#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


int fd;

int main(int argc, char **argv)
{
  
	if (argc < 2)
		perror("Please, put a serial port\n\r");
		
	printf("Status open port: %s\n\r",argv[1]);

	struct termios t;
		
	if((fd = open(argv[1],O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
		perror("could not open port\n\r");
	
	if(tcgetattr(fd,&t) < 0)
		perror("get termios attributtes");
	
	cfmakeraw(&t);

	t.c_cflag |= (CLOCAL | CREAD);
	cfsetspeed(&t,B115200);

	if(tcsetattr(fd,TCSANOW,&t))
		perror("failed tcsetatribute");


	char buf[10];
	unsigned char data[10];
	unsigned short dist = 0;
	unsigned char ver[4]={0X5A, 0x04, 0x01, 0x00};
	int ct;
	while(1)
	{	
		
		//write(fd,"AT\r\n",4);
		//write(fd,ver,4);
		//while(*buf != '\0')
		//{
		if((ct = read(fd,(void*)data,10)) < 0 )
			perror("Failed to read data");
		//}
                
		//printf("%d PORT DATA: %s\n\r",ct, buf);
		/*
		while(*buf == 0x59 && *(buf+1) == 0x59)		
		printf("distance: %d cm\n\r",(short)(((0x0000 | *(buf+3)) << 8) | (0x0000 | *(buf+2))));
		*/
		
		printf("%x%x%x%x\n\r",data[0],data[1],data[2],data[3]);
		
		//memset(buf,'\0',sizeof(buf));
		sleep(1);
	}

	return 0;
}


