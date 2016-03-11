ROOTDIR=./core

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware -lpthread

all: main

main : ./hw/hw.o main.o ctx.o sem.o
	$(CC) $(CFLAGS) -o main main.o $(LIBS)

main.o: main.c ctx.o sem.o hw/hw.o
	$(CC) $(CFLAGS) -c main.c

ctx.o : ./hw/hw.c ./hw/hw.h ctx.c ctx.h
	$(CC) $(CFLAGS) -c ctx.c

sem.o : ctx.o sem.c sem.h
	$(CC) $(CFLAGS) -c sem.c

clean:
	-rm *.o main vdiskA.bin vdiskB.bin .#* *~
