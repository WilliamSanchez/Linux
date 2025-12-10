CFLAGS = -O 
CC = g++ 

all: main

main: main.o thread_safe_queue.h
	$(CC) $(CFLAGS) -o main main.o
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp 

clean: 
	rm -f main *.o *~


