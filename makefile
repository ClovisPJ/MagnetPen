CC=gcc
CFLAGS=-lbcm2835 -g -Isrc/vector

read: src/read.c src/lsm303c/lsm303c.c src/lsm303c/lsm303c-spi.c src/vector/vector.c
	$(CC) -o out/read src/read.c src/lsm303c/lsm303c.c src/lsm303c/lsm303c-spi.c src/vector/vector.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f out/*
