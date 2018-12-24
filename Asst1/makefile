CC = gcc
CCFLAGS = -ansi -pedantic -Wall -D_BSD_SOURCE -std=c99 -lm

all:sorter

sorter: scannerCSVsorter.c 
	$(CC) $(CCFLAGS) -o sorter scannerCSVsorter.c 

clean:
	rm -f sorter
