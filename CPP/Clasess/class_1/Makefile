CFLAGS = -O 
DEPS =
OBJS = punto.o herencia1.o herencia2.o
CC = g++ 
CFLAGS = #-I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: punto herencia1 herencia2

punto: punto.o
	$(CC) -o $@ $^ $(CFLAGS)
	
herencia1: herencia1.o
	$(CC) -o $@ $^ $(CFLAGS)
	
herencia2: herencia2.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o punto herencia1 herencia2 *~



