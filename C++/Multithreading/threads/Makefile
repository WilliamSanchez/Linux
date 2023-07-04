CFLAGS = -O 
CC = g++ 

all: main

main: main.o 
	$(CC) $(CFLAGS) -o main main.o
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp 

clean: 
	rm -f class *.o *~


