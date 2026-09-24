CC = gcc
CFLAGS = -Wall -Wextra -g
HUFFMAN_BIN = huffman.exe
BITIO_TEST_BIN = tests/bitio_test.exe
HUFFMAN_TEST_BIN = tests/huffman_test.exe
HUFFMAN_TREE_TEST_BIN = tests/huffman_tree_test.exe
PRIORITY_QUEUE_TEST_BIN = tests/priority_queue_test.exe

.PHONY: all test measure clean

all: $(HUFFMAN_BIN) test

$(HUFFMAN_BIN): src/main.c src/huffman.c src/priority_queue.c src/bitio.c src/huffman.h src/priority_queue.h src/bitio.h
	$(CC) $(CFLAGS) -Isrc src/main.c src/huffman.c src/priority_queue.c src/bitio.c -o $(HUFFMAN_BIN)

test: $(BITIO_TEST_BIN) $(HUFFMAN_TEST_BIN) $(HUFFMAN_TREE_TEST_BIN) $(PRIORITY_QUEUE_TEST_BIN)
	$(BITIO_TEST_BIN)
	$(HUFFMAN_TEST_BIN)
	$(HUFFMAN_TREE_TEST_BIN)
	$(PRIORITY_QUEUE_TEST_BIN)

$(BITIO_TEST_BIN): tests/bitio_test.c src/bitio.c src/bitio.h
	$(CC) $(CFLAGS) -Isrc tests/bitio_test.c src/bitio.c -o $(BITIO_TEST_BIN)

$(HUFFMAN_TEST_BIN): tests/huffman_test.c src/huffman.c src/priority_queue.c src/bitio.c src/huffman.h src/priority_queue.h src/bitio.h
	$(CC) $(CFLAGS) -Isrc tests/huffman_test.c src/huffman.c src/priority_queue.c src/bitio.c -o $(HUFFMAN_TEST_BIN)

$(HUFFMAN_TREE_TEST_BIN): tests/huffman_tree_test.c src/huffman.c src/priority_queue.c src/bitio.c src/huffman.h src/priority_queue.h src/bitio.h
	$(CC) $(CFLAGS) -Isrc tests/huffman_tree_test.c src/huffman.c src/priority_queue.c src/bitio.c -o $(HUFFMAN_TREE_TEST_BIN)

$(PRIORITY_QUEUE_TEST_BIN): tests/priority_queue_test.c src/priority_queue.c src/priority_queue.h src/huffman.h
	$(CC) $(CFLAGS) -Isrc tests/priority_queue_test.c src/priority_queue.c -o $(PRIORITY_QUEUE_TEST_BIN)

measure: $(HUFFMAN_BIN)
	python tests/compression_ratio.py tests/samples/repeated.txt repeated.huf

clean:
	del /Q $(HUFFMAN_BIN) $(BITIO_TEST_BIN) $(HUFFMAN_TEST_BIN) $(HUFFMAN_TREE_TEST_BIN) $(PRIORITY_QUEUE_TEST_BIN) *.huf test.bin 2>NUL