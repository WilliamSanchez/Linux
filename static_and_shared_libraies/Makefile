CC = gcc
CFLAGS=-I. -L.
#DEPS = libw.h
OBJ = program.o fred.o bill.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: libfoo.a program

libfoo.a: lib.h fred.o bill.o
	ar -rs libfoo.a bill.o fred.o

program: $(OBJ) libfoo.a
	@echo ejecutable: 
	gcc -o program program.c $(CFLAGS) -lfoo


.PHONY: clean 

clean:
	rm -f *.o program *~ *.so *.a
