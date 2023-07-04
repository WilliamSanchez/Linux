CC = gcc
CFLAGS= -I. -Wall
OBJ = fifo1.o fifo2.o

#	$@	--> Name of the current target
#	$< 	--> Name of the current prerequisite
#	$* 	--> Name of the current prerequisite without any sufex 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# pthread.o: pthread.c
#	gcc -c -o pthread.o pthread.c

all: fifo1 fifo2
	
fifo1: fifo1.o
	$(CC) -o $@ $^ $(CFLAGS)

fifo2: fifo2.o
	$(CC) -o $@ $^ $(CFLAGS)

#pthread: pthread.o 
#     gcc -o pthread pthread.o

.PHONY: clean

clean:
	rm -f *.o fifo1 fifo2 *~
	
	
	
