ifneq ($(KERNELRELEASE),)
	obj-m := touchScreenDriver.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
#KERNELDIR := /lib/modules/2.6.32-358.23.2.el6.i686/build
#PWD := $(shell pwd) 
#modules:
#	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules 
#modules_install:
#	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install 
clean:
	make -C $(KERNELDIR) M=${PWD} clean
endif
