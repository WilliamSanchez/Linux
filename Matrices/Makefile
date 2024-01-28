CC = gcc
DEPS = matrices.h -lm
OBJ = main.o matrices.o 
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
