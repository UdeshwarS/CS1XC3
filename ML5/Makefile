CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

TARGET = lab
OBJS = main.o BubbleSort.o SelectionSort.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c BubbleSort.h SelectionSort.h
BubbleSort.o: BubbleSort.c BubbleSort.h
SelectionSort.o: SelectionSort.c SelectionSort.h

clean:
	$(RM) $(OBJS) $(TARGET)
