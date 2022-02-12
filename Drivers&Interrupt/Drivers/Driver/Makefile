obj-m += driver_v1.o driver_v2.o
KDIR = /lib/modules/$(shell uname -r)/build
	
all:
	make -C $(KDIR) M=$(shell pwd) modules
clean:
	make -C $(KDIR) M=$(shell pwd) clean
