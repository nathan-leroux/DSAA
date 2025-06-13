#include "binary_tree.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Binary Tree example
 *
 * tree_print()     - O(n) helper function (traverses tree)
 * tree_minimum()   - O(logn)
 * tree_search()    - O(logn)
 * tree_delete()    - O(1)
 * tree_insert()    - O(logn)
 *
 */

void
tree_print(struct tree* selected)
{
  if (selected == NULL) {
    return;
  }

  tree_print(selected->left);

  printf("%d - ", selected->value);
  if (selected->parent != NULL) {
    printf("(parent: %d) ", selected->parent->value);
  }
  if (selected->left != NULL) {
    printf("(left: %d) ", selected->left->value);
  }
  if (selected->right != NULL) {
    printf("(right: %d) ", selected->right->value);
  }
  if (selected->right == NULL && selected->left == NULL) {
    printf("LEAF");
  }
  if (selected->parent == NULL) {
    printf("ROOT");
  }
  printf("\n");

  tree_print(selected->right);
}

struct tree*
tree_minimum(struct tree* selected)
{
  if (selected == NULL) {
    return NULL;
  }

  if (selected->left == NULL) {
    return selected;
  }

  return tree_minimum(selected->left);
}

struct tree*
tree_search(struct tree* btree, int target)
{
  // target doesn't exist
  if (btree == NULL) {
    return NULL;
  }

  // found it
  if (btree->value == target) {
    return btree;
  }

  if (btree->value > target) {
    return tree_search(btree->left, target);
  } else {
    return tree_search(btree->right, target);
  }
}

void
tree_delete(struct tree** tree, struct tree* selected)
{
  // find the pointer that links to the parent
  struct tree** parent_ref;

  if (selected->parent == NULL) {
    parent_ref = tree;
  } else if (selected->parent->left == selected) {
    parent_ref = &(selected->parent->left);
  } else {
    parent_ref = &(selected->parent->right);
  }

  // count the children
  int children = 0;
  if (selected->left != NULL) {
    ++children;
  }
  if (selected->right != NULL) {
    ++children;
  }

  // perform the deletion based on how many children the node has
  if (children == 0) {
    *parent_ref = NULL;
  } else if (children == 1) {
    if (selected->left != NULL) {
      *parent_ref = selected->left;
      selected->left->parent = selected->parent;
    } else {
      *parent_ref = selected->right;
      selected->right->parent = selected->parent;
    }
  } else {
    struct tree* minimum = tree_minimum(selected->right);

    int value_switch = minimum->value;
    minimum->value = selected->value;
    selected->value = value_switch;

    tree_delete(tree, minimum);
  }
}

void
tree_insert(struct tree** selected, struct tree* parent, int value)
{
  if (*selected == NULL) {
    struct tree* new_node = malloc(sizeof(struct tree));

    new_node->value = value;
    new_node->parent = parent;
    new_node->left = NULL;
    new_node->right = NULL;

    *selected = new_node;
    return;
  }

  // if we're not at the end yet
  struct tree** next_node;
  if (value < (*selected)->value) {
    next_node = &((*selected)->left);
  } else {
    next_node = &((*selected)->right);
  }

  tree_insert(next_node, *selected, value);
}

void
example_binary_tree(void)
{
  struct tree* btree = NULL;
  struct tree* selected;

  printf("## Binary Tree example\n");
  printf("##\n");
  printf("## inserting values into binary tree\n");
  printf("##\n");

  tree_insert(&btree, NULL, 5);
  tree_insert(&btree, NULL, 2);
  tree_insert(&btree, NULL, 3);
  tree_insert(&btree, NULL, 4);
  tree_insert(&btree, NULL, 1);

  tree_print(btree);

  printf("##\n");
  printf("## Deleting element 2\n");
  printf("##\n");

  selected = tree_search(btree, 2);
  tree_delete(&btree, selected);

  tree_print(btree);

  printf("##\n");
  printf("## Minimum\n");
  printf("##\n");
  printf("min: %d\n", tree_minimum(btree)->value);
}
