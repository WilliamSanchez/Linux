obj-m += completions.o
obj-m += driver_squeleton.o
obj-m += intro_task.o
obj-m += mutex_example.o
obj-m += spinlock_example.o
obj-m += tasklet_example.o
obj-m += workqueue_example.o

PWD := $(CURDIR)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
