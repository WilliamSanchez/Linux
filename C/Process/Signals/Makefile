CC  = gcc
DEPS = #shm_com.h
OBJ =  signal1.o alarm.o StopCont.o sigaction.o comunication_signal.o
CFLAGS = -I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: signal1 alarm StopCont sigaction comunication_signal

sgnal1: signal1.o
	$(CC) -o $@ $^ $(CFLAGS)
	
alarm: alarm.o
	$(CC) -o $@ $^ $(CFLAGS)

StopCont: StopCont.o
	$(CC) -o $@ $^ $(CFLAGS)
	
sigaction: sigaction.o
	$(CC) -o $@ $^ $(CFLAGS)
	
comunication_signal: comunication_signal.o
	$(CC) -o $@ $^ $(CFLAGS)
	

.PHONY: clean

clean:
	rm -f *.o signal1 alarm StopCont sigaction comunication_signal *~
