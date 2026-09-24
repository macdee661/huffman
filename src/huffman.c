#include "huffman.h"
#include "priority_queue.h"

#include <string.h>

void count_frequencies(FILE *fp, int frequencies[256]){

    int c;
    while((c = fgetc(fp)) != EOF){
        frequencies[c]++;
    }
}

struct Node *build_tree(int freq[256]){

    struct PQ pq = {0}; 

    for(int i = 0; i < 256; i++){
        
        if(freq[i] > 0){

            struct Node *node = malloc(sizeof(*node));

            node->c = (unsigned char)i;
            node->frequency = freq[i];
            node->left = NULL;
            node->right = NULL;

            push(&pq, node);
        }
    }

    while(pq_size(&pq) > 1){
        struct Node *left = pop(&pq);
        struct Node *right = pop(&pq);

        struct Node *parent_node = malloc(sizeof(*parent_node));

        parent_node->c = 0;
        parent_node->frequency = left->frequency + right->frequency;
        parent_node->left =left;
        parent_node->right = right;

        push(&pq, parent_node);

    }

    return pop(&pq);

}

void free_tree(struct Node *node){
    if(node == NULL){
        return;
    }

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void generate_codes(struct Node *node, char path[256], int depth, char codes[256][256]){
    if(node->left == NULL && node->right == NULL){
        path[depth] = '\0';
        strcpy(codes[node->c], path);
        return;
    };
    path[depth] = '0';
    generate_codes(node->left, path, depth+1, codes);
    path[depth] = '1';
    generate_codes(node->right, path, depth+1, codes);

}

void encode(FILE *fp, char codes[256][256], struct BitIO *writer){
    rewind(fp);

    int c;

    while((c = fgetc(fp)) != EOF){
            for(int j = 0; codes[c][j] != '\0'; j++){
                write_bit(codes[c][j] == '1', writer);
            };
    }

    flush(writer);
}

void decode(struct Node *root, int total_count, struct BitIO *reader, FILE *output){
    for(int count = 0; count < total_count; count++){
        struct Node *node = root;

        while(node->left != NULL || node->right != NULL){
            int bit = read_bit(reader);
            node = bit == 0 ? node->left : node->right;
        }

        fputc(node->c, output);
    }
}

void write_header(int freq[256], int total_count, FILE *output){
    fwrite(&total_count, sizeof(int), 1, output);
    fwrite(freq, sizeof(int), 256, output);
}

void read_header(int freq[256], int *total_count, FILE *input){
    fread(total_count, sizeof(int), 1, input);
    fread(freq, sizeof(int), 256, input);
}

void compress(const char *input_path, const char *output_path){

    FILE *in = fopen(input_path, "rb");
    FILE *out = fopen(output_path, "wb");
    if (!in || !out) return;

    int frequencies[256] = {0};
    count_frequencies(in, frequencies);

    int total = 0;
    for (int i = 0; i < 256; i++) total += frequencies[i];

    struct Node *root = build_tree(frequencies);

    char path[256];
    char codes[256][256];
    generate_codes(root, path, 0, codes);

    write_header(frequencies, total, out);
    struct BitIO writer;

    writer_init(&writer, out);
    rewind(in);
    encode(in, codes, &writer);

    free_tree(root);
    fclose(in);
    fclose(out);

}

void decompress(const char *input_path, const char *output_path){
    FILE *in = fopen(input_path, "rb");
    FILE *out = fopen(output_path, "wb");
    if (!in || !out) {
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    int frequencies[256] = {0};
    int total_count = 0;
    read_header(frequencies, &total_count, in);

    struct Node *root = build_tree(frequencies);
    if (root != NULL && total_count > 0) {
        struct BitIO reader;
        reader_init(&reader, in);
        decode(root, total_count, &reader, out);
    }

    free_tree(root);
    fclose(in);
    fclose(out);
}