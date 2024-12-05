CC = gcc
CFLAGS = -Wall -std=c99
OBJ = main.o update_validator.o

all: program

program: $(OBJ)
	$(CC) $(OBJ) -o update_validator

main.o: main.c update_validator.h
	$(CC) $(CFLAGS) -c main.c

update_validator.o: update_validator.c update_validator.h
	$(CC) $(CFLAGS) -c update_validator.c

clean:
	rm -f *.o program
