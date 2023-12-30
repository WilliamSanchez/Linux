#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

char read_data=0x00;

char readBuffer[3];
char readData[8];

static short dist = 0xFFFF;

int main(int argc, char **argv)
{
 

	int file;
	
	if((file = open("/dev/i2c-2", O_RDWR)) < 0)
	{
		perror("failed to open the bus\n");
		return 1;
	}
	
	if(ioctl(file, I2C_SLAVE, 0x10))
	{
	 	perror("Failed to connect to the sensor \n");
	 	return 1;	
	}
	
	char writeBuffer[1]={0x0A};
	
	if(write(file, writeBuffer, 1) != 1 )
	{
		perror("Failed to reset the read address\n");
		return 1;
	}

	
	
	if(read(file,readBuffer,3) != 3){
	
		perror("Failed to read in the buffer\n");
		return 1;
	
	}
	
	printf("The version is: %x-%x%x\n", readBuffer[0], readBuffer[2], readBuffer[1]);
	
	
	while(1)
	{
		system("clear"); 	 
	 	if(write(file, (void*)&read_data, 1) != 1 )
		{
			perror("Failed to reset the read address\n");
			return 1;
		}
	
		if(read(file,readData,8) != 8){
		
			perror("Failed to read in the buffer\n");
			return 1;	
		}    
		
		dist = 0xFFFF;
		dist &= (readData[1]<< 8 | readData[0]);
		
		printf("Distance= %d cm\n\r", dist);
		sleep(1);
	
	}	
	close(file);
	
	
	

	return 0;
}


