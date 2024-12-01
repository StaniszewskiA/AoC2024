CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJ = main.o reconcile.o

EXEC = reconcile

all: $(EXEC)

main.o: main.c reconcile.h
	$(CC) $(CFLAGS) -c main.c

reconcile.o: reconcile.c reconcile.h
	$(CC) $(CFLAGS) -c reconcile.c

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

clean:
	rm -f $(OBJ) $(EXEC)
