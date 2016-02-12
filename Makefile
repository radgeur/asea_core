ROOTDIR=./core

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic
CFLAGS  += -g -m32
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware -lpthread

all: main

main : main.o
	$(CC) $(CFLAGS) -o main main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	-rm *.o main vdiskA.bin vdiskB.bin .#* *~
