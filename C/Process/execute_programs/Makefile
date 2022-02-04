CC  = gcc
DEPS = #shm_com.h
OBJ =  exec.o #shm1.o shm2.o
CFLAGS = #-I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: exec

exec: exec.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o exec *~
