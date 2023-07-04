CC = gcc
CFLAGS= -I. -Wall
OBJ = Lists_v1.o Lists_v2.o

#	$@	--> Name of the current target
#	$< 	--> Name of the current prerequisite
#	$* 	--> Name of the current prerequisite without any sufex 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# pthread.o: pthread.c
#	gcc -c -o pthread.o pthread.c

all: Lists_v1 Lists_v2
	
Lists_v1: Lists_v1.o
	$(CC) -o $@ $^ $(CFLAGS)

Lists_v2: Lists_v2.o
	$(CC) -o $@ $^ $(CFLAGS)

#pthread: pthread.o 
#     gcc -o pthread pthread.o

.PHONY: clean

clean:
	rm -f *.o Lists_v1 Lists_v2 *~
	
	
	
