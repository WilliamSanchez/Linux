CC  = gcc
DEPS = #shm_com.h
OBJ =  program.o #shm1.o shm2.o
CFLAGS = -I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: program

program: program.o
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o program *~
