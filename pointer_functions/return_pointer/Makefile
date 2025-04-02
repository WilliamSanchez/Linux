CC = gcc
OBJ = return_pointer.o
CFLAGS = -I. 
LIBS=-lm

all: return_pointer

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

return_pointer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f *.o return_pointer *~



