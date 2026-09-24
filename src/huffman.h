#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "bitio.h"
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
void free_tree(struct Node *node);
void generate_codes(struct Node *node, char path[256], int depth, char codes[256][256]);
void encode(FILE *fp, char codes[256][256], struct BitIO *writer);
void decode(struct Node *root, int total_count, struct BitIO *reader, FILE *output);
void write_header(int freq[256], int total_count, FILE *output);
void read_header(int freq[256], int *total_count, FILE *input);
void compress(const char *input_path, const char *output_path);
void decompress(const char *input_path, const char *output_path);
#endif