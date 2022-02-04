CC  = gcc
DEPS = #shm_com.h
OBJ =  process1.o process2.o process3.o pipe1.o pipe2.o fifo1.o main1.o main2.o ProcessPipe.o
CFLAGS = -I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: process1 process2 process3 pipe1 pipe2 ProcessPipe

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
	
fifo1: fifo1.o
	$(CC) -o $@ $^ $(CFLAGS)
	
main1: main1.o
	$(CC) -o $@ $^ $(CFLAGS)
	
main2: main2.o
	$(CC) -o $@ $^ $(CFLAGS)

ProcessPipe: ProcessPipe.o
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o process1 process2 process3 pipe1 pipe2  fifo1 main1 main2 ProcessPipe *~
