CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -O2
TARGET = assignment2
SRCS = convert.c main.c

all: run

run: $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	./$(TARGET) > output.txt

clean:
	rm -f $(TARGET) output.txt