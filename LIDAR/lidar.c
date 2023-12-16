#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
   int port;
   struct termios t;

	if (argc < 2)
		perror("Please, put a serial port\n\r");
	printf("Hola PORT: %d %s\n\r",argc, argv[1]);
	
	if((port = open(argv[1],O_RDWR | O_NONBLOCK)) < 0)
	{
	  perror("could not open port\n\r");
	}

	if(tcgetattr(port,&t) < 0)
		perror("get termios attributtes");
	
	cfmakeraw(&t);

	t.c_cflag |= CLOCAL;
	cfsetspeed(&t,B115200);

	if(tcsetattr(port,TCSANOW,&t))
	   perror("failed tcsetatribute");

	char buf[100];
	int ct;
	while(1)
	{
                 ct = read(port,&buf,sizeof(buf));
		printf("%d PORT DATA: %x\n\r",ct, *buf);
		sleep(1);
	}

	return 0;
}

