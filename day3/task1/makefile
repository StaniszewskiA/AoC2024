CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o mul_parser.o
TARGET = sum_mul

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c mul_parser.h
	$(CC) $(CFLAGS) -c main.c

mul_parser.o: mul_parser.c mul_parser.h
	$(CC) $(CFLAGS) -c mul_parser.c

clean:
	del $(OBJ) $(TARGET)
