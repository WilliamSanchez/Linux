CC = gcc
CFLAGS= -I. -Wall -lpthread
OBJ = pthread_cond_variable_broadcast.o

#	$@	--> Name of the current target
#	$< 	--> Name of the current prerequisite
#	$* 	--> Name of the current prerequisite without any sufex 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# pthread.o: pthread.c
#	gcc -c -o pthread.o pthread.c

all: pthread_cond_variable_broadcast
	
pthread_cond_variable_broadcast: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#pthread: pthread.o 
#     gcc -o pthread pthread.o

.PHONY: clean

clean:
	rm -f *.o pthread_cond_variable_broadcast *~
	
	
	
