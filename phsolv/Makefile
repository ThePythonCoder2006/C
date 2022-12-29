CC=gcc
COMMON_CFLAGS=-Wall -Wextra
CFLAGS=$(COMMON_CFLAGS) -O3
DEBUG_CFLAGS=$(COMMON_CFLAGS) -ggdb

comp:
	$(CC) main.c -o main $(CFLAGS)
	./main

db:
	$(CC) main.c -o main $(DEBUG_CFLAGS)
	gdb main