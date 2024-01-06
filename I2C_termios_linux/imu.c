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

#define DEVID 0x00
#define BUFFER_SIZE 6
#define samples   50


unsigned char readData[BUFFER_SIZE];


unsigned char writeBuffer[2] = {0x75, 0x1B}; 
unsigned char read_data = 0x43;
unsigned char PWR_MGMT_1 = 0x6B;  
unsigned char who_am_i;
   
unsigned char enable[2];
unsigned char data;

static short gyro_x = 0xFFFF;
static short gyro_y = 0xFFFF;
static short gyro_z = 0xFFFF;

static float calibrate_gyro_x = 0;
static float calibrate_gyro_y = 0;
static float calibrate_gyro_z = 0;

static float data_gyro_x =0.0;
static float data_gyro_y =0.0;
static float data_gyro_z =0.0;

static float pitch =0.0;
static float yaw =0.0;
static float roll =0.0;

int file;

int set_Data(char *reg, int size)
{

    if(write(file,reg,size) != size)
    {
     perror("failed to connect the sensor \n");
     return 1;   
   }
   return 0;
};


int get_Data(char *reg, int size, char *data)
{
    if(write(file,reg,1) != 1)
    {
     perror("failed to connect the sensor \n");
     return 1;   
   }
   
   if(read(file,data, size) != size)
   {
     perror("failed to read the sensor \n");
     return 1;   
   }
   
   return 0;
};

int main()
{

   printf("Starting the IMU test application\n\r");
   
   if((file = open("/dev/i2c-2", O_RDWR)) < 0)
   {
     perror("failed to open the bus\n");
     return 1;
   }

   if(ioctl(file, I2C_SLAVE, 0x68) < 0)
   {
     perror("failed to connect the sensor \n");
     return 1;   
   }

 /*  
    if(write(file,&(*(writeBuffer)),1) != 1)
    {
     perror("failed to connect the sensor \n");
     return 1;   
   }
  */ 
   
   if(get_Data(&writeBuffer, 1, &who_am_i) != 0)
   {
     perror("failed to read the sensor \n");
     return 1;   
   }
         
   printf("The device ID is: 0x%02x\n",who_am_i);
   
   ////////////////////////////////////////////////////
   ////////////////////////////////////////////////////

   
    if(set_Data(&enable, 2) != 0)
    {
     perror("failed to connect the sensor \n");
     return 1;   
   }
   
   if(get_Data(&(*(writeBuffer+1)), 1, &data) != 0)
   {
     perror("failed to read the sensor \n");
     return 1;   
   }
   

   
   printf("The register 0x%02x is: 0x%02x\n",writeBuffer[1], data);
   ////////////////////////////////////////////////////
   ////////////////////////////////////////////////////
   
   enable[0] = 0x6B; enable[1] = 0x01;
      
    if(set_Data(&enable, strlen(enable)) != 0)
    {
     perror("failed to connect the sensor \n");
     return 1;   
   }
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////			CALIBRATION		////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
   
  int s = 0;
  short c_gyro_x = 0;
  short c_gyro_y = 0;
  short c_gyro_z = 0;

  while(s < samples)
  {
	
	if(get_Data(&read_data, BUFFER_SIZE, &readData) != 0 )
	{
		perror("Failed to reset the read address\n");
		return 1;
	}
	
	gyro_x = 0xFFFF; gyro_y = 0xFFFF; gyro_z = 0xFFFF;
	gyro_x &= (readData[0]<< 8 | readData[1]);
	gyro_y &= (readData[2]<< 8 | readData[3]);
	gyro_z &= (readData[4]<< 8 | readData[5]); 
  
  	c_gyro_x += gyro_x;
  	c_gyro_y += gyro_y;
  	c_gyro_z += gyro_z;
  	s++;
  	
  	usleep(50000);
  } 
   
  calibrate_gyro_x = c_gyro_x/samples;
  calibrate_gyro_y = c_gyro_y/samples;
  calibrate_gyro_z = c_gyro_z/samples;
   
   
   
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 

   while(1)
   {
   		system("clear");   			 
	 	if(get_Data(&read_data, BUFFER_SIZE, &readData) != 0 )
		{
			perror("Failed to reset the read address\n");
			return 1;
		} 
		
		gyro_x = 0xFFFF; gyro_y = 0xFFFF; gyro_z = 0xFFFF;
		gyro_x &= (readData[0]<< 8 | readData[1]);
		gyro_y &= (readData[2]<< 8 | readData[3]);
		gyro_z &= (readData[4]<< 8 | readData[5]);
		
		data_gyro_x = (((float)gyro_x-calibrate_gyro_x)*.060975f);
  		data_gyro_y = (((float)gyro_y-calibrate_gyro_y)*.060975f);
  		data_gyro_z = (((float)gyro_z-calibrate_gyro_z)*.060975f);
		

		pitch = pitch+data_gyro_x*0.1;
		yaw = yaw+data_gyro_y*0.1;
		roll =roll+data_gyro_z*0.1;
		
		printf("Gyro x: %f\n\r",pitch);
		printf("Gyro y: %f\n\r",yaw);
		printf("Gyro z: %f\n\r",roll);
		
		usleep(100000);
   
   }

   
   close(file);
   
   return 0;
}
