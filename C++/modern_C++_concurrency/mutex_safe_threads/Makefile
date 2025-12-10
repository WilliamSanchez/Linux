CFLAGS = -O 
CC = g++ 

all: main

main: main.o thread_safe_stack.h race_condition_trivial_stack.h
	$(CC) $(CFLAGS) -o main main.o
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp 

clean: 
	rm -f main *.o *~


