#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


int open_port(char *port);
int fd;

int main(int argc, char **argv)
{
  
	if (argc < 2)
		perror("Please, put a serial port\n\r");
		
	printf("Status open port: %d\n\r",open_port(argv[1]));




	char buf[10];
	char *data;
	unsigned short dist = 0;
	unsigned char ver[4]={0X5A, 0x04, 0x01, 0x00};
	int ct;
	while(1)
	{	
		
		//write(fd,"AT\r\n",4);
		//write(fd,ver,4);
		//while(*buf != '\0')
		//{
		     ct = read(fd,&buf,10);
		//}
                
		//printf("%d PORT DATA: %s\n\r",ct, buf);
		while(*buf == 0x59 && *(buf+1) == 0x59)
		
		printf("distance: %d cm\n\r",(short)(((0x0000 | *(buf+3)) << 8) | (0x0000 | *(buf+2))));
		memset(buf,'\0',sizeof(buf));
		sleep(1);
	}

	return 0;
}


int open_port(char *port)
{
	
	struct termios t;
		
	if((fd = open(port,O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
		perror("could not open port\n\r");
	
	if(tcgetattr(fd,&t) < 0)
		perror("get termios attributtes");
	
	cfmakeraw(&t);

	t.c_cflag |= (CLOCAL | CREAD);
	cfsetspeed(&t,B115200);

	if(tcsetattr(fd,TCSANOW,&t))
		perror("failed tcsetatribute");
	
 return fd;
}

