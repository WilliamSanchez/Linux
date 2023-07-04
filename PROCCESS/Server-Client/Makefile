CC = gcc
#CC = arm-cortex_a8-linux-gnueabihf-gcc
DEPS = cliente.h
OBJ = shm1.o shm2.o
CFLAGS = -I. 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: server client

server: server.o

	$(CC) -o $@ $^ $(CFLAGS)

client: client.o

	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean 

clean:
	rm -f *.o server client *~
