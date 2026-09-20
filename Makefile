CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = my3proc
SOURCES = main3.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
