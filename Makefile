CC = gcc
CFLAGS = -Wall -Wextra -g
BITIO_TEST_BIN = tests/bitio_test.exe
HUFFMAN_TEST_BIN = tests/huffman_test.exe
HUFFMAN_TREE_TEST_BIN = tests/huffman_tree_test.exe
PRIORITY_QUEUE_TEST_BIN = tests/priority_queue_test.exe

.PHONY: all test clean

all: test

test: $(BITIO_TEST_BIN) $(HUFFMAN_TEST_BIN) $(HUFFMAN_TREE_TEST_BIN) $(PRIORITY_QUEUE_TEST_BIN)
	$(BITIO_TEST_BIN)
	$(HUFFMAN_TEST_BIN)
	$(HUFFMAN_TREE_TEST_BIN)
	$(PRIORITY_QUEUE_TEST_BIN)

$(BITIO_TEST_BIN): tests/bitio_test.c src/bitio.c src/bitio.h
	$(CC) $(CFLAGS) -Isrc tests/bitio_test.c src/bitio.c -o $(BITIO_TEST_BIN)

$(HUFFMAN_TEST_BIN): tests/huffman_test.c src/huffman.c src/priority_queue.c src/huffman.h src/priority_queue.h
	$(CC) $(CFLAGS) -Isrc tests/huffman_test.c src/huffman.c src/priority_queue.c -o $(HUFFMAN_TEST_BIN)

$(HUFFMAN_TREE_TEST_BIN): tests/huffman_tree_test.c src/huffman.c src/priority_queue.c src/huffman.h src/priority_queue.h
	$(CC) $(CFLAGS) -Isrc tests/huffman_tree_test.c src/huffman.c src/priority_queue.c -o $(HUFFMAN_TREE_TEST_BIN)

$(PRIORITY_QUEUE_TEST_BIN): tests/priority_queue_test.c src/priority_queue.c src/priority_queue.h src/huffman.h
	$(CC) $(CFLAGS) -Isrc tests/priority_queue_test.c src/priority_queue.c -o $(PRIORITY_QUEUE_TEST_BIN)

clean:
	del /Q $(BITIO_TEST_BIN) $(HUFFMAN_TEST_BIN) $(HUFFMAN_TREE_TEST_BIN) $(PRIORITY_QUEUE_TEST_BIN) 2>NUL