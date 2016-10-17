#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "key.c"

int log_search = 0;

// inserts into the tree example
// (milk)
// > insert mill
//  (mil)
//  |   |
// (k) (l)
// > insert mix
//  (mi)
//  |  |
// (x)(l)
//    | |
//   (k)(l)
// > insert mile
//  (mi)
//  |  |
// (x)(l)____
//    |  |  |
//   (k)(l)(e)

// Implements a radix tree
// Radix tree splits a string and separates it into common parts
typedef struct node {
  node_key_t *part;
  struct node *first_child;
  struct node *next_sibling;
} node_t;

node_t *node_new(node_key_t *part) {
  node_t *node = NULL;
  node = malloc(sizeof(node_t));
  node->part = part;
  node->first_child = NULL;
  node->next_sibling = NULL;


  return node;
}

// creates a new node from  a string.
node_t *node_snew(char *s) {
  node_key_t *dest = malloc(sizeof(node_key_t));
  strncpy(*dest, s, strlen(s));
  return node_new(dest);
}

void node_insert(node_t **root, node_key_t *val) {
  node_t *node = *root;

  // if this is a null node, we just add the value to this.
  if (strlen(*node->part) == 0 && node->first_child == NULL) {
    node->part = val;
    return;
  }

  int i;

  for (i = 0; i < strlen(*node->part); i++) {
    if ((*val)[i] != (*node->part)[i]) {

      // Split the node into two parts depending on the incoming
      // values. The original node takes over as the

      // create a 'next_node' which takes over this nodes children.
      node_t *next_node = node_new(from(node->part, i));
      next_node->first_child = node->first_child;
      node->first_child = next_node;


      // create a new sibling.
      node_t *new_sibling = node_new(from(val, i));
      next_node->next_sibling = new_sibling;


      // original node takes a new name.
      node->part = up_to(val, i);

      return;
    }
  }

  // the piece after where we've gotten too.
  node_key_t *next_part = from(val, i);

  // We reached the end, that means everything matches with this insert so far.
  if (node->first_child == NULL) {
    // this node doesn't have any children yet! we can add ourselves as the first.
    node->first_child = node_new(next_part);
    return;
  }

  node_t *cur;

  if (strlen(*next_part) == 0) {
    // hey we made it!, make sure we add an empty leaf node here to mark that
    // this key exists.
    cur = node->first_child;
    while (cur->next_sibling != NULL) {
      cur = cur->next_sibling;
    }
    cur->next_sibling = node_new(next_part);
    return;
  }

  cur = node->first_child;
  while(1) {
    // printf("child node insert: %s %s\n", *next_part, *cur->part);

    // we see if we can even go down the path with the sibling.
    if (strlen(*cur->part) > 0 && (*next_part)[0] == (*cur->part)[0]) {
      // we found a sibling to continue on with!
      // insert will walk through this sibling and either split it or find a
      // child to add it to.
      return node_insert(&cur, next_part);
    }

    if (cur->next_sibling == NULL) {
      break;
    }

    cur = cur->next_sibling;
  }

  // No siblings start with what this starts with, so, lets create the sibling!
  // Note, since we reached the end 'cur' should be the last sibling.
  // printf("adding next part %s as sibling of %s\n", *next_part, *cur->part);
  cur->next_sibling = node_new(next_part);
}

void node_sinsert(node_t **root, char *sval) {
  node_key_t *dest = malloc(sizeof(node_key_t));
  strncpy(*dest, sval, strlen(sval));
  return node_insert(root, dest);
}

node_t *node_find(node_t *root, char *sval) {
  node_t *node = root;
  int idx = 0;
  int nidx = 0;
  int depth = 1;
  int sval_len = strlen(sval);

  while (node != NULL) {

    if (log_search) {
      printf("find nidx=%d nval=%c idx=%d sval=%c d=%d node=%s\n",
        nidx, (*node->part)[nidx], idx, sval[idx], depth, *node->part);
    }

    if (strlen(*node->part) == 0) {
      // this is a null node, move forward without incrementing the counter.
      if (node->next_sibling == NULL) {
        node = node->first_child;
      } else {
        node = node->next_sibling;
      }
      nidx = 0;
      continue;
    }

    if (sval[idx] == (*node->part)[nidx]) {

      if (idx + 1 == sval_len) {
        return node;
      }

      if (strlen(*node->part) == nidx + 1) {
        // if we've reached the end of this node, we should go to it's child.
        node = node->first_child;
        nidx = 0;
      } else {
        // keep going if we can move through this still.
        nidx++;
      }

      idx++;
      continue;
    }

    if (node->next_sibling == NULL) {
      node = node->first_child;
    } else {
      node = node->next_sibling;
    }

    depth++;
    nidx = 0;
  }

  return NULL;
}

void print_tree(node_t *root) {
  node_t *cur = root->first_child;
  printf("\n");

  if (strlen(*root->part) == 0) {
    printf("(null)\n");
  } else {
    printf("%s\n", *root->part);
  }


  while(cur != NULL) {
    printf("| %s |", *cur->part);
    cur = cur->next_sibling;
  }
  printf("\n");

  cur = root->first_child;
  while(cur != NULL) {
    if (cur->first_child != NULL) {
      print_tree(cur);
    }
    cur = cur->next_sibling;
  }
}
