CFLAGS = -O 
CC = g++ 

all: class

class: class.o vivos.o 
	$(CC) $(CFLAGS) -o class class.o vivos.o 
class.o: class.cpp 
	$(CC) $(CFLAGS) -c class.cpp 
vivos.o: vivos.cpp 
	$(CC) $(CFLAGS) -c vivos.cpp 
clean: 
	rm -f class *.o *~


