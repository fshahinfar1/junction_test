#! vim: set noet ts=4 sw=4:
SOURCES = boot.c
CFLAGS = -Wall -g -O2
LDFLAGS =
CC = gcc

.PHONY: default run comp

default: comp

run: boot
	junction_run ./my.config -- ./boot

comp: boot

boot: $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

