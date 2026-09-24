#include "huffman.h"
#include "priority_queue.h"

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