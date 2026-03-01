CFLAGS = -O 
CC = g++ 

all: main

main: main.o 
	$(CC) $(CFLAGS) -o main main.o thread_safe_queue.h
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp 

clean: 
	rm -f main *.o *~


