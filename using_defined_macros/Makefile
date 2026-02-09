CC = gcc
OBJ = main.o
CFLAGS = 

all: main

%.o: %.c
	$(CC) -DENABLE_MACRO $(CFLAGS) -c -o $@ $< $(LIBS)
	
#%.o: %.c
#	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

main: $(OBJ)
	$(CC)  $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f *.o main *~



