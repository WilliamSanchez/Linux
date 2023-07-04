CFLAGS = -std=c++17  
CC = g++ 

all: main

main: main.o 
	$(CC) $(CFLAGS) -o main main.o -lpthread
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp 

clean: 
	rm -f main *.o *~


