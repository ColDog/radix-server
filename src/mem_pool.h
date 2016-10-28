#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __MEM_POOL_H
#define __MEM_POOL_H

/**
 * Block
*/
typedef struct block {
  int size;
  void *block;
  struct block *next;
} block_t;

void block_print(block_t *block) {
  printf("| ");
  for (int i = 0; i < block->size; i++) {
    printf("%02x | ", ((uint8_t*) block->block)[i]);
  }
  printf(" |\n");
}

/**
 * Pool
*/
typedef struct pool {
  int block_size;
  int count;
  int used;
  block_t *head;
  block_t *tail;
  struct pool *next;
} pool_t;

void pool_reduce(pool_t *pool, int amount) {
  for (int i = 0; i < amount; i++) {
    block_t *block = pool->head;
    pool->head = block->next;
    free(block->block);
    free(block);
  }
}

void pool_insert(pool_t *pool, block_t *block) {
  if (pool->head == NULL) {
    pool->head = block;
    pool->tail = block;
    pool->count = 1;
    return;
  }

  pool->tail->next = block;
  pool->tail = block;
  pool->count++;
}

block_t *pool_provision(pool_t *pool) {
  block_t *block = malloc(sizeof(block_t));
  block->block = malloc(pool->block_size);
  block->size = pool->block_size;

  pool_insert(pool, block);
  return block;
}

void pool_return(pool_t *pool, block_t *block) {
  if (pool->head == NULL) {
    pool->head = block;
    pool->tail = block;
    pool->count = 1;
    pool->used--;
    return;
  }

  pool->tail->next = block;
  pool->tail = block;
  pool->count++;
  pool->used--;
}

block_t *pool_pop(pool_t *pool) {
  if (pool->head == NULL) {
    return pool_provision(pool);
  }

  block_t *block = pool->head;
  if (pool->count == 1) {
    // TODO: log warning.
    pool->head = NULL;
    pool->tail = NULL;
    pool->count = 0;
    pool->used++;
    return block;
  }

  pool->head = block->next;
  pool->count--;
  pool->used++;
  return block;
}

/**
 * Pool Manager
*/
struct pool_mgr *pmgr;
int initialized = 0;

typedef struct pool_mgr {
  struct pool *head;
  struct pool *tail;
} pool_mgr_t;

void mp_init() {
  if (initialized) return;

  pmgr = malloc(sizeof(pool_mgr_t));
  pmgr->head = NULL;
  pmgr->tail = NULL;
  initialized = 1;
}

void mp_reduce(int size, int amount) {
  pool_t *cur = pmgr->head;
  while (cur != NULL) {
    if (cur->block_size == size) {
      pool_reduce(cur, amount);
      return;
    }
    cur = cur->next;
  }
}

void mp_seed(int size, int blocks) {

  pool_t *new = malloc(sizeof(pool_t));
  new->count = 0;
  new->used = 0;
  new->block_size = size;
  new->head = NULL;
  new->tail = NULL;
  new->next = NULL;

  for (int i = 0; i < blocks; i++) {
    pool_provision(new);
  }

  if (pmgr->head == NULL) {
    pmgr->head = new;
    pmgr->tail = new;
    return;
  }

  if (size < pmgr->head->block_size) {
    new->next = pmgr->head;
    pmgr->head = new;
    return;
  }

  pool_t *cur = pmgr->head;
  while (cur != NULL) {
    if (size > cur->block_size) {
      new->next = cur->next;
      cur->next = new;
      return;
    }
    cur = cur->next;
  }

  pmgr->tail->next = new;
  pmgr->tail = new;
}

block_t *mp_alloc(int size) {
  pool_t *cur = pmgr->head;

  if (size < cur->block_size) {
    return pool_pop(cur);
  }

  while (cur->next != NULL) {
    if (size > cur->next->block_size) {
      // the next one is too big. Have to allocate this one.
      return pool_pop(cur);
    }
    cur = cur->next;
  }

  if (size < cur->block_size) {
    return pool_pop(cur);
  }

  // nothing matches in this size.
  return NULL;
}

void mp_dealloc(block_t *block) {
  pool_t *cur = pmgr->head;
  while (cur != NULL) {
    if (cur->block_size == block->size) {
      // reset the block to null values.
      memset(block->block, '\0', block->size);
      pool_return(cur, block);
      return;
    }
    cur = cur->next;
  }
}

block_t *mp_realloc(block_t *block, int size) {
  block_t *new = mp_alloc(size);
  memcpy(new->block, block->block, block->size);
  mp_dealloc(block);
  return new;
}

int mp_stats_total() {
  int total = 0;
  pool_t *cur = pmgr->head;
  while (cur != NULL) {
    total += cur->block_size * cur->count;
    cur = cur->next;
  }
  return total;
}

int mp_stats_used() {
  int total = 0;
  pool_t *cur = pmgr->head;
  while (cur != NULL) {
    total += cur->block_size * cur->used;
    cur = cur->next;
  }
  return total;
}

int mp_stats_available() {
  return mp_stats_total() - mp_stats_used();
}

void mp_stats_print() {
  printf("----stats----\n");

  pool_t *cur = pmgr->head;
  int i = 1;
  while (cur != NULL) {
    printf("%d) pool %d, used: %d, avail: %d\n", i, cur->block_size, cur->used, cur->count);
    cur = cur->next;
    i++;
  }

  printf("total: %d\n", mp_stats_total());
  printf("used:  %d\n", mp_stats_used());
  printf("avail: %d\n", mp_stats_available());
}

#endif
