#include "priority_queue.h"

#include <assert.h>

int main(void){
    struct PQ pq = {0};
    struct Node nodes[] = {
        {.frequency = 5},
        {.frequency = 1},
        {.frequency = 4},
        {.frequency = 2},
        {.frequency = 3},
    };
    int expected_frequencies[] = {1, 2, 3, 4, 5};

    for(size_t index = 0; index < sizeof(nodes) / sizeof(nodes[0]); index++){
        push(&pq, &nodes[index]);
    }

    assert(pq_size(&pq) == 5 && "pq_size should report all pushed nodes");

    for(size_t index = 0; index < sizeof(expected_frequencies) / sizeof(expected_frequencies[0]); index++){
        struct Node *node = pop(&pq);
        assert(node != NULL && "pop should return a node while the queue is non-empty");
        assert(node->frequency == expected_frequencies[index] && "pop should return nodes in ascending frequency order");
        assert(pq_size(&pq) == (int)(4 - index) && "pq_size should decrease after each pop");
    }

    assert(pop(&pq) == NULL && "pop should return NULL for an empty queue");
    assert(pq_size(&pq) == 0 && "pq_size should be zero after all nodes are popped");

    return 0;
}