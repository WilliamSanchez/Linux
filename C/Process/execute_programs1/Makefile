CC  = gcc
DEPS = #shm_com.h
OBJ =  upper.o useupper.o #shm1.o shm2.o
CFLAGS = #-I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: upper useupper

upper: upper.o
	$(CC) -o $@ $^ $(CFLAGS)

useupper: useupper.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o upper useupper *~
