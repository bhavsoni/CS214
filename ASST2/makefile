all: multiThreadSorter

multiThreadSorter: multiThreadSorter_thread.c
	gcc -g -Wall -Werror -lpthread multiThreadSorter_thread.c -o multiThreadSorter 


clean:
	rm -f multiThreadSorter
