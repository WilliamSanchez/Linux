CC = gcc
CFLAGS=-I.
#DEPS = libw.h
OBJ = serial_data_read.o #main.o libw.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: serial_data_read

serial_data_read: $(OBJ)
	@echo ejecutable: 
	gcc -o $@ $^ $(CFLAGS)


.PHONY: clean 

clean:
	rm -f *.o serial_data_read *~
