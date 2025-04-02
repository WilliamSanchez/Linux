CC = gcc
OBJ = point_functions.o


%.o: %.c
	$(CC) -c -o $@ $<

all: point_functions

main:
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o point_functions *~



