CC = gcc
CFLAGS = -Wall -std=c99
OBJ = main.o task1.o task2.o

all: program

program: $(OBJ)
	$(CC) $(OBJ) -o day7

main.o: main.c task1.h task2.h
	$(CC) $(CFLAGS) -c main.c

task1.o: task1.c task1.h
	$(CC) $(CFLAGS) -c task1.c

task2.o: task2.c task2.h
	$(CC) $(CFLAGS) -c task2.c

clean:
	rm -f *.o program
