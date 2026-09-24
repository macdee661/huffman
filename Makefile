CC = gcc
CFLAGS = -Wall -Wextra -g
TEST_BIN = tests/bitio_test.exe

.PHONY: all test clean

all: test

test: $(TEST_BIN)
	$(TEST_BIN)

$(TEST_BIN): tests/bitio_test.c src/bitio.c src/bitio.h
	$(CC) $(CFLAGS) -Isrc tests/bitio_test.c src/bitio.c -o $(TEST_BIN)

clean:
	del /Q $(TEST_BIN) 2>NUL