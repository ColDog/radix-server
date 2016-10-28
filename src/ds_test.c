#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_pool.h"
#include "ds.h"

char *test_alloc_ds() {
  mp_init();
  mp_seed(25, 25);
  mp_seed(35, 35);
  ds_t *ds = ds_new(20);
  return NULL;
}

char *test_realloc_ds() {
  ds_t *str = ds_new(20);
  str = ds_grow(str, 27);
  return NULL;
}

char *test_append_ds() {
  ds_t *dest = ds_string("testing");
  ds_t *src = ds_string("123");
  dest = ds_append(dest, src);

  return assert_str_equal("testing123", dest->buf);
}

char *test_prepend_ds() {
  ds_t *dest = ds_string("testing");
  ds_t *src = ds_string("123");
  dest = ds_prepend(dest, src);

  return assert_str_equal("123testing", dest->buf);
}

char *test_append_realloc_ds() {
  mp_seed(25, 1);
  mp_seed(100, 1);
  ds_t *dest = ds_string("testing");
  int old = dest->block->size;
  ds_t *src = ds_string("areallylongstringthatshouldoverflowtheoneitisappendingto");
  dest = ds_append(dest, src);
  int new = dest->block->size;

  char *test_1 = assert_int_equal(25, old);
  if (test_1 != NULL) {
    return test_1;
  }

  return assert_int_equal(100, new);
}

void ds_tests() {
  describe("ds (dynamic string)");
  test("alloc", test_alloc_ds);
  test("realloc", test_realloc_ds);
  test("append", test_append_ds);
  test("append realloc", test_append_realloc_ds);
}
