#ifndef BITIO_H
#define BITIO_H
#include <stdio.h>
#include <stdlib.h>

struct BitIO {
    FILE *file;
    int counter;
    unsigned char pen;
};


void writer_init(struct BitIO *io);
void write_bit(int bit, struct BitIO *io);
void flush(struct BitIO *io);

void reader_init(struct BitIO *io);
int read_bit(struct BitIO *io);

#endif