CC = gcc
CFLAGS = -Wall -std=c99
OBJ = main.o day10.o

all: day10

day10: $(OBJ)
	$(CC) $(OBJ) -o day10

main.o: main.c day10.h 
	$(CC) $(CFLAGS) -c main.c

day10.o: day10.c day10.h
	$(CC) $(CFLAGS) -c day10.c

clean:
	rm -f *.o day10
