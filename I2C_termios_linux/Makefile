CC=gcc
CCFLAGS=-Wall

all:	lidar imu

lidar: lidar.c
	$(CC) $(CCFLAGS) $^ -o $@

lidar: imu.c
	$(CC) $(CCFLAGS) $^ -o $@
	
clean:
	rm -f lidar imu
