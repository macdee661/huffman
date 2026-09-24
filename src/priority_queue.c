#include "priority_queue.h"

void push(struct PQ *pq, struct Node *node){
    pq->heap[pq->size] = node;
    pq->size++;
};

struct Node *pop(struct PQ *pq){
    if(pq->size == 0){
        return NULL;
    }
    int min_index = 0;
    for(int index = 1; index < pq->size; index++){
        struct Node *curr_node = pq->heap[index];
        struct Node *min_node = pq->heap[min_index];

        if (min_node->frequency > curr_node->frequency){
            min_index = index;
        };
    };

    struct Node *temp_node  = pq->heap[min_index];
    pq->heap[min_index] = pq->heap[pq->size-1];
    pq->size--;

    return temp_node;

};

int pq_size(struct PQ *pq){
    return pq->size;
};