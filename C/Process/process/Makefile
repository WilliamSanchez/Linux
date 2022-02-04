CC  = gcc
DEPS = #shm_com.h
OBJ =  process1.o process2.o process3.o pipe1.o pipe2.o
CFLAGS = -I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: process1 process2 process3 pipe1 pipe2

process1: process1.o
	$(CC) -o $@ $^ $(CFLAGS)
	
process2: process2.o
	$(CC) -o $@ $^ $(CFLAGS)

process3: process3.o
	$(CC) -o $@ $^ $(CFLAGS)

pipe1: pipe1.o
	$(CC) -o $@ $^ $(CFLAGS)
	
pipe2: pipe2.o
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o process1 process2 process3 *~
