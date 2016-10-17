#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef KEY_H
#define KEY_H

// Key types
typedef char node_key_t[255];

node_key_t *from(node_key_t *cur, int from) {
  node_key_t *dest = calloc(255, sizeof(node_key_t));
  memcpy(dest, *cur + from, strlen(*cur));
  return dest;
}

node_key_t *up_to(node_key_t *cur, int up_to) {
  node_key_t *dest = calloc(255, sizeof(node_key_t));
  memcpy(dest, *cur, up_to);
  return dest;
}

#endif
