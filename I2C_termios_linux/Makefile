CC=gcc
CCFLAGS=-Wall

lidar_i2c: lidar_i2c.c
	$(CC) $(CCFLAGS) $^ -o $@

#lidar: lidar.c
#	$(CC) $(CCFLAGS) $^ -o $@
	
clean:
	rm -f lidar lidar_i2c *.o *.bin
