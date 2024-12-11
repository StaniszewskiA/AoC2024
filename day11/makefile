CC = gcc
CFLAGS = -Wall -std=c11
OBJ = main.o solver.o

all: blink_solver

blink_solver: $(OBJ)
	$(CC) $(OBJ) -o blink_solver

main.o: main.c solver.h
	$(CC) $(CFLAGS) -c main.c

solver.o: solver.c solver.h
	$(CC) $(CFLAGS) -c solver.c

clean:
	rm -f $(OBJ) blink_solver
