#include "huffman.h"

#include <assert.h>

static int validate_tree(struct Node *node){
    if(node->left == NULL || node->right == NULL){
        assert(node->left == NULL && node->right == NULL && "each leaf should have zero children");
        return 1;
    }

    assert(node->frequency == node->left->frequency + node->right->frequency &&
           "internal frequency should equal the sum of its children");

    return validate_tree(node->left) + validate_tree(node->right);
}

static void free_tree(struct Node *node){
    if(node == NULL){
        return;
    }

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main(void){
    int frequencies[256] = {0};
    frequencies['a'] = 3;
    frequencies['b'] = 2;
    frequencies['c'] = 1;

    struct Node *root = build_tree(frequencies);
    assert(root != NULL && "build_tree should return a root for non-empty input");
    assert(root->frequency == 6 && "root frequency should equal the total input count");
    assert(validate_tree(root) == 3 && "leaf count should equal the distinct-byte count");

    free_tree(root);
    return 0;
}