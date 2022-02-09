CC = gcc
OBJ = tabla_hash.o


%.o: %.c
	$(CC) -c -o $@ $<

all: tabla_hash

main:
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o tabla_hash *~



