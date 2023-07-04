CC = gcc
OBJ = embedded_usart.o


%.o: %.c
	$(CC) -c -o $@ $<

all: embedded_usart

main:
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o tabla_hash *~



