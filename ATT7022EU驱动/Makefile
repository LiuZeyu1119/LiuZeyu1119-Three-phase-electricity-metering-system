# SPDX-License-Identifier: GPL-2.0
#
# Makefile for metering ic drivers
#

ifneq ($(KERNELRELEASE),) 
obj-m:= ATT7022EU.o
#obj-m:= ATT7022EU-spi.o
else

ARCH := arm
#CROSS_COMPILE := /opt/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
CROSS_COMPILE := arm-none-linux-gnueabihf-

KERNELDIR:=/home/liuzeyu/Desktop/kernel

PWD:=$(shell pwd)
endif

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(info info text)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.order *.symvers    
