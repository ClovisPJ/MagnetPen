CC=gcc
CFLAGS=-lbcm2835 -g

read: src/read.c src/lsm303c/lsm303c.c src/lsm303c/lsm303c-spi.c
	$(CC) -o out/read src/read.c src/lsm303c/lsm303c.c src/lsm303c/lsm303c-spi.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f out/*
