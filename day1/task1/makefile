CC = gcc

CFLAGS = -Wall -Wextra -std=c11

TARGET = reconcile

OBJ = main.o reconcile.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c reconcile.h
	$(CC) $(CFLAGS) -c main.c

reconcile.o: reconcile.c reconcile.h
	$(CC) $(CFLAGS) -c reconcile.c

clean:
	rm -f $(OBJ) $(TARGET)
