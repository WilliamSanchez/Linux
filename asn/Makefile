CC = gcc
LIBDIR=e2sm_rc

INCLDIR = $(LIBDIR)
INCLDIR += $(LIBDIR)/headers

INCLUDE = $(addprefix -I,$(INCLDIR))

SRCS := $(wildcard e2sm_rc/*.c e2sm_rc/lib/*.c)



.PHONY:	main all clean
all: main

main: main.c $(SRCS
	gcc main.c -I/home/william/Documents/programming/ANSI_C/asn/e2sm_rc -I/home/william/Documents/programming/ANSI_C/asn/e2sm_rc/headers -L/home/william/Documents/programming/ANSI_C/asn/e2sm_rc -le2smrcwrapper -o main
	$(CC) -I/$(INCLDIR) -L/home/william/Documents/programming/ANSI_C/asn/$(LIBDIR) -o main -le2smrcwrapper
	

