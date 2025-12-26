CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = food_ordering_system
SOURCES = main.c menu.c order_queue.c order_history.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = menu.h order_queue.h order_history.h

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean

