CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = pattern_search
OBJS = main.o pattern_search.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c pattern_search.h
	$(CC) $(CFLAGS) -c main.c

pattern_search.o: pattern_search.c pattern_search.h
	$(CC) $(CFLAGS) -c pattern_search.c

clean:
	rm -f $(OBJS) $(TARGET)
