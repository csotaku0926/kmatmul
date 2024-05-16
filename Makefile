NAME := matmul
CC = gcc
CFLAGS = -O1 -g -Wall 
obj-m := $(NAME).o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: matmul.c users
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	@insmod $(NAME).ko
	
users: users.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rmmod $(NAME)
	@rm -f users perf/trace.txt