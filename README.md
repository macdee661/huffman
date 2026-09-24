# Huffman Coding

A small C implementation of Huffman compression and decompression, with tests and a Python script for measuring compression size.

## Build and Test

Requirements:

- GCC
- GNU Make
- Python 3

Build the program and run the test suite:

```powershell
make
```

Run the compression measurement with the included sample:

```powershell
make measure
```

## Usage

Compress a file:

```powershell
.\huffman.exe compress input.txt output.huf
```

Decompress an archive:

```powershell
.\huffman.exe decompress output.huf recovered.txt
```

The short forms `c` and `d` are also supported.

To compress a file, verify its round trip, and print compression statistics in one command:

```powershell
python tests/compression_ratio.py input.txt output.huf
```

The script compares the original input with the decompressed output byte-for-byte. The archive size includes the frequency-table header, so small files may become larger after compression.

## Layout

```text
src/                 Huffman implementation and command-line program
tests/               C tests and compression measurement script
tests/samples/       Sample input files
Makefile             Build, test, measure, and cleanup commands
```

Clean generated binaries and test artifacts:

```powershell
make clean
```
