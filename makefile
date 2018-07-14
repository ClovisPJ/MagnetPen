CC=gcc
CFLAGS=-lbcm2835

read: src/read.c src/lsm303c/lsm303c.c
	$(CC) -o read src/read.c src/lsm303c/lsm303c.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f out/*
