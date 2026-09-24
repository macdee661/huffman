#include "bitio.h"

#include <assert.h>
#include <stdio.h>

int main(void){

    int bits[] = {1,0,1,1,1,0,0,0,1,1};

    FILE *fp = fopen("test.bin", "wb+");
    assert(fp != NULL && "tmpfile should create a writable file");

    struct BitIO test_struct;
    writer_init(&test_struct, fp);
    assert(test_struct.counter == 0 && "writer_init should reset counter");
    assert(test_struct.pen == 0 && "writer_init should reset pen");
    assert(test_struct.file == fp && "writer_init should set the output file");

    for(size_t i = 0; i < sizeof(bits) / sizeof(bits[0]); i++){
        write_bit(bits[i], &test_struct);
    }

    flush(&test_struct);

    rewind(fp);
    reader_init(&test_struct, fp);
    assert(test_struct.counter == 0 && "reader_init should reset counter");
    assert(test_struct.pen == 0 && "reader_init should reset pen");

    for(size_t i = 0; i < sizeof(bits) / sizeof(bits[0]); i++){
        int next_bit = read_bit(&test_struct);
        assert(next_bit == bits[i] && "read_bit should return the expected bit");
    }

    fclose(fp);
    return 0;
}