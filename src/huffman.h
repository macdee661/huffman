#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
#include <stdlib.h>

struct Node {
    unsigned char c;
    int frequency;
    struct Node *left;
    struct Node *right;
};
void count_frequencies(FILE *fp, int frequencies[256]);
struct Node *build_tree(int freq[256]);

#endif