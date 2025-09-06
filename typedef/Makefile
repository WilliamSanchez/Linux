CC = gcc
OBJ = typedef_case-i.o
CFLAGS = -I. 
LIBS=-lm

all: typedef_case-i

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

return_pointer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f *.o typedef_case-i *~



