CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = binary_search
SOURCE = binary_search.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
