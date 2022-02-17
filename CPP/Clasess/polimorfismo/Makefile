CFLAGS = -O 
DEPS =
OBJS = polimorfismo.o
CC = g++ 
CFLAGS = #-I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: polimorfismo

polimorfismo: polimorfismo.o
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o polimorfismo *~



