#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define DEVID 0x00
#define BUFFER_SIZE 40

int main()
{

   int file;
   printf("tarting the IMU test application\n\r");
   
   if((file = open("/dev/i2c-2")) < 0)
   {
     perror("failed to open the bus\n");
     return 1;
   }

   if(ioctl(file, I2C_SLAVE, 0x68) < 0)
   {
     perror("failed to connect the sensor \n");
     return 1;   
   }

    unsigned char writeBuffer = 0x75;
/*
    if(write(file, writeBuffer,1) != 1)
        {
     perror("failed to connect the sensor \n");
     return 1;   
   }
   
   */
   
   unsigned char who_am_i[BUFFER_SIZE];
   
   if(read(file, who_am_i, 1) != 1)
   {
     perror("failed to read the sensor \n");
     return 1;   
   }
   
   printf("The device ID is: 0x%02x\n",*who_am_i);
   
   close(file);
   
   return 0;
}
