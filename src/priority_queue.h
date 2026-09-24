#include "huffman.h"
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct PQ {

    struct Node *heap[256];
    int size;
};

void push(struct PQ *pq, struct Node *node);
struct Node *pop(struct PQ *pq);
int pq_size(struct PQ *pq);

#endif