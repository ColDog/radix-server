#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_pool.h"

#ifndef __DS_H
#define __DS_H

typedef struct ds {
  block_t *block;
  int len;
  char buf[];
} ds_t;

ds_t *ds_new(int size) {
  block_t *b = mp_alloc(sizeof(ds_t) + (sizeof(char) * size));
  ds_t *new = b->block;
  new->len = 0;
  new->block = b;
  return new;
}

ds_t *ds_string(char *str) {
  int l = strlen(str);
  ds_t *d = ds_new(l);
  for (int i = 0; i < l; i++) {
    d->buf[i] = str[i];
  }
  d->len = l;
  return d;
}

ds_t *ds_grow(ds_t *str, int size) {
  block_t *b = mp_realloc(str->block, size);
  str = b->block;
  str->block = b;
  return str;
}

ds_t *ds_insert(ds_t *dest, ds_t *source, int start, int offset, int size) {
  int newlen = start + size;
  int newsize = (newlen * sizeof(char)) + sizeof(int) + sizeof(dest->block);

  if (newsize > dest->block->size) {
    dest = ds_grow(dest, newsize);
  }

  for (int i = 0; i < newlen; i++) {
    dest->buf[start + i] = source->buf[offset + i];
  }
  dest->len = newlen;
  return dest;
}

ds_t *slice(ds_t *src, int start, int end) {
  ds_t *new = ds_new(end - start);
  for (int i = 0; i < (end - start); i++) {
    new->buf[i] = src->buf[start + i];
  }
  src->len = end - start;
  return new;
}

ds_t *ds_append(ds_t *dest, ds_t *src) {
  return ds_insert(dest, src, dest->len, 0, src->len);
}

ds_t *ds_prepend(ds_t *dest, ds_t *src) {
  return ds_insert(src, dest, src->len, 0, dest->len);
}

#endif
