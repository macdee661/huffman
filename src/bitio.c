#include "bitio.h"

void writer_init(struct BitIO *io){
    io->counter = 0;
    io->pen = 0;
}

void reader_init(struct BitIO *io){
    io->counter = 0;
    io->pen = 0;
}

void write_bit(int bit, struct BitIO *io){
    io->pen = (unsigned char)((io->pen << 1) | (bit & 1));
    io->counter++;

    if (io->counter >= 8){
        io->counter = 0;
        fputc(io->pen, io->file);
        io->pen = 0;
    };
}

void flush(struct BitIO *io){
    if(io->counter > 0){
        fputc((int)(io->pen << (8 - io->counter)), io->file);
        io->counter = 0;
        io->pen = 0;
    };
}

int read_bit(struct BitIO *io){
    if (io->counter == 0){
        int byte = fgetc(io->file);


        io->pen = (unsigned char)byte;
        io->counter = 8;
    }

    int bit = (io->pen & 0x80) != 0;
    io->pen <<= 1;
    io->counter--;
    return bit;
}