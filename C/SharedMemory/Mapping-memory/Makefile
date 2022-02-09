#CC = gcc
CC = arm-cortex_a8-linux-gnueabihf-gcc
OBJ = mmap-read.o mmap-write.o mmap.o


%.o: %.c
	$(CC) -c -o $@ $< 

all: mmap-read mmap-write mmap

mmap-read: mmap-read.o

	$(CC) -o $@ $^ 

mmap-write: mmap-write.o

	$(CC) -o $@ $^ 

mmap: mmap.o

	$(CC) -o $@ $^ 


.PHONY: clean 

clean:
	rm -f *.o mmap-read mmap-write mmap *~


#   ./mmap-write /tmp/integer-file
#   cat /tmp/integer-file
#    ./mmap-read /tmp/integer-file	{enter}
#   cat /tmp/integer-file
