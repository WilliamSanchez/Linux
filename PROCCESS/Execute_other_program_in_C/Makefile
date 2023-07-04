CC = gcc
CFLAGS= -I. -Wall
OBJ = exe_c.o pipe4.o

#	$@	--> Name of the current target
#	$< 	--> Name of the current prerequisite
#	$* 	--> Name of the current prerequisite without any sufex 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# pthread.o: pthread.c
#	gcc -c -o pthread.o pthread.c

all: exe_c pipe4
	
exe_c: exe_c.o
	$(CC) -o $@ $^ $(CFLAGS)

pipe4: pipe4.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o pipe4 exe_c *~
	
	
	
