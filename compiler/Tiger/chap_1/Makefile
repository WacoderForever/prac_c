CC = gcc
CFLAGS = -Wall -g
all: prog
prog: main.o util.o slp.o prog1.o
	$(CC) main.o util.o slp.o prog1.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
util.o: util.c
	$(CC) $(CFLAGS) -c util.c
slp.o: slp.c
	$(CC) $(CFLAGS) -c slp.c
prog1.o: prog1.c
	$(CC) $(CFLAGS) -c prog1.c
clean:
	rm -f *.o a.out