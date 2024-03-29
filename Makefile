#Makefile wrdmttns
CFLAGS  = -Wall -std=c99 -O3
default: all

all: main.o scandict.o output.o input.o algorithms.o graphf.o heap1.o
	gcc $(CFLAGS) -o wrdmttns main.o scandict.o output.o input.o algorithms.o graphf.o heap1.o

main.o: main.c main.h
	gcc  $(CFLAGS) -c main.c

scandict.o: scandict.c scandict.h
	gcc  $(CFLAGS) -c scandict.c

output.o: output.c output.h
	gcc  $(CFLAGS) -c output.c

input.o: input.c input.h
	gcc  $(CFLAGS) -c input.c

algorithms.o: algorithms.c algorithms.h
	gcc  $(CFLAGS) -c algorithms.c

graphf.o: graphf.c graphf.h
	gcc  $(CFLAGS) -c graphf.c

heap1.o: heap1.c heap1.h
	gcc  $(CFLAGS) -c heap1.c
	
clean:
	rm -rf *o $(objects) wrdmttns
