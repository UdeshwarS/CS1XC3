CC      = gcc
CFLAGS  = -Wall -Wextra
INPUT_C = ../input.c

# Default build (0.3s per tick)
tick_demo: tick_demo.c $(INPUT_C)
	$(CC) $(CFLAGS) tick_demo.c $(INPUT_C) -o tick_demo

# Fast clock (0.1s per tick)
fast: tick_demo.c $(INPUT_C)
	$(CC) $(CFLAGS) -DTICK_DECISECONDS=1 tick_demo.c $(INPUT_C) -o tick_demo

# Medium clock (0.5s per tick)
medium: tick_demo.c $(INPUT_C)
	$(CC) $(CFLAGS) -DTICK_DECISECONDS=5 tick_demo.c $(INPUT_C) -o tick_demo

# Slow clock (1.0s per tick)
slow: tick_demo.c $(INPUT_C)
	$(CC) $(CFLAGS) -DTICK_DECISECONDS=10 tick_demo.c $(INPUT_C) -o tick_demo

# Basic demo
basic: basic_demo.c 
	$(CC) $(CFLAGS) basic_demo.c -o tick_demo

clean:
	rm -f tick_demo

.PHONY: fast medium slow clean