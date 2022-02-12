obj-m += thread_EPoll.o
KDIR = /lib/modules/$(shell uname -r)/build
	
all:
	gcc -o user_program user_program.c
	make -C $(KDIR) M=$(shell pwd) modules

clean:
	rm -rf user_program
	make -C $(KDIR) M=$(shell pwd) clean

