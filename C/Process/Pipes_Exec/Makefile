CC  = gcc
DEPS = #shm_com.h
OBJ =  pipe1.o pipe2.o #shm1.o shm2.o
CFLAGS = #-I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: pipe1 pipe2

pipe1: pipe1.o
	$(CC) -o $@ $^ $(CFLAGS)

pipe2: pipe2.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o pipe1 pipe2 *~
