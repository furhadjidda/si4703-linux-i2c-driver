obj-m += si4703.o

platform-objs := si4703.o

SRC = /home/furhad/Development/Si4703-FM-Driver/si4703-fmrds-driver-example/code

LINUX_3_2_27 = /home/furhad/Development/Linux-kernel-dev/linux

PREFIX = /home/furhad/Development/Linux-kernel-dev/tools/arm-bcm2708/arm-bcm2708-linux-gnueabi/bin/arm-bcm2708-linux-gnueabi-

all:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(PREFIX) -C $(LINUX_3_2_27) M=$(SRC) modules

clean:
	$(MAKE) -C $(LINUX_3_2_27) M=$(SRC) clean
