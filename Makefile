CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
TARGET = firewall

obj-m += $(TARGET).o

default:
		$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
		rm -f *.o .*.cmd .*.flags *.mod.c *.order
		rm -f *.symvers
		rm -f .*.*.cmd *~ *.*~ TODO.*
		rm -fR .tmp*
		rm -rf .tmp_versions
		rm -f *.h.gch

disclean: clean
		rm *.ko
