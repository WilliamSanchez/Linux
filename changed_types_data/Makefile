CC = gcc
DEPS = 
OBJ = main.o 
CFLAGS = -I. 
LIBS=-lm

all: main

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 
	
main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean 

clean:
	rm -f *.o main  *~
