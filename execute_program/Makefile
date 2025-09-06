CC = gcc
CFLAGS= -I. -Wall
OBJ = exec_program.o 

#	$@	--> Name of the current target
#	$< 	--> Name of the current prerequisite
#	$* 	--> Name of the current prerequisite without any sufex 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)


all: exec_program
	
exe_c: exec_program.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o exec_program *~
	
	
	
