CFLAGS = -O 
CC = g++ 

INC_DIRS = ../common
INC_DIRS += .

INCLUDE = $(addprefix -I,$(INC_DIRS))

SRCS = main.cpp
SRCS += ../common/utils.c

all: main

main: $(SRCS)
	$(CC) $(INCLUDE)  $(CFLAGS) $^ -o $@ 

clean: 
	rm -f main *.o *~


