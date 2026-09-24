#include "huffman.h"

#include <assert.h>
#include <stdio.h>

int main(void){
    FILE *file = fopen("tests/samples/scratch_text.txt", "r");
    assert(file != NULL && "huffman test input file cannot open or does not exist");

    int freqs[256] = {0};

    count_frequencies(file, freqs);
    assert(freqs['a'] == 2 && "frequency of 'a' should be 2");
    assert(freqs['d'] == 2 && "frequency of 'd' should be 2");
    assert(freqs['m'] == 1 && "frequency of 'm' should be 1");
    assert(freqs['c'] == 1 && "frequency of 'c' should be 1");
    assert(freqs['o'] == 1 && "frequency of 'o' should be 1");
    assert(freqs['l'] == 1 && "frequency of '1' should be 1");

    fclose(file);
    return 0;
}