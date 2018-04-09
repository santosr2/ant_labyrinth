CC=gcc
CFLAGS=-W -Wall -Wextra -std=c99 -pedantic
LIBS=-lncurses
EXEC=alab
SRC=$(wildcard *.c)

all: $(EXEC)

$(EXEC): $(SRC)
	@$(CC) $(CFLAGS) $(LIBS) -o $@ $^


.PHONY: clean


clean:
	@rm $(EXEC)