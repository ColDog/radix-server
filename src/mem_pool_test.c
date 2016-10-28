#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_pool.h"

char *test_create_mem_pool() {
  mp_init();
  mp_seed(30, 24);
  mp_seed(30, 30);
  block_t *b = mp_alloc(23);

  b = mp_realloc(b, 27);

  mp_dealloc(b);
  return NULL;
}

void mem_pool_tests() {
  describe("mem pool");
  test("create mem pool", test_create_mem_pool);
}
