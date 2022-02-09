CC = gcc
OBJ = machine_state.o


%.o: %.c
	$(CC) -c -o $@ $<

all: machine_state

main:
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o tabla_hash *~



