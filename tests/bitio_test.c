#include "bitio.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    static const int expected_bits[] = {1, 0, 1, 0, 0, 1, 0, 1};
    const char *temporary_path = "tests/bitio_test.tmp";
    struct BitIO io = {0};
    FILE *file = fopen(temporary_path, "w+b");

    assert(file != NULL);

    io.file = file;
    writer_init(&io);

    for (size_t index = 0; index < sizeof(expected_bits) / sizeof(expected_bits[0]); index++) {
        write_bit(expected_bits[index], &io);
    }
    flush(&io);

    assert(fflush(file) == 0);
    assert(fseek(file, 0, SEEK_SET) == 0);

    reader_init(&io);
    for (size_t index = 0; index < sizeof(expected_bits) / sizeof(expected_bits[0]); index++) {
        assert(read_bit(&io) == expected_bits[index]);
    }

    fclose(file);
    remove(temporary_path);
    puts("bitio tests passed");
    return 0;
}
