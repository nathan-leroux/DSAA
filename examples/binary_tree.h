#ifndef BINARYTREE_H
#define BINARYTREE_H

struct tree {
    int value;
    struct tree* parent;
    struct tree*left;
    struct tree* right;
};


void tree_print(struct tree*);
struct tree* tree_minimum(struct tree*);
struct tree* tree_search(struct tree*, int);
void tree_delete(struct tree*);
void tree_insert(struct tree**, struct tree*, int);
void example_binary_tree(void);


#endif
