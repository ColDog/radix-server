#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "radix.c"


char *rand_str(int max) {
  int size = (rand() % max) + 1;
  const char selections[] = "abcdefghijklmnopqrstuvwxyz0123456789";

  char *dest = malloc(size);

  int i;
  for (i = 0; i < size; i++) {
    int key = rand() % 34;
    dest[i] = selections[key];
  }
  dest[i+1] = '\0';

  return dest;
}

char *can_find(node_t **root, char *val) {
  node_t *res = node_find(*root, val);
  if (res == NULL) {
    return "cannot find value";
  }
  return NULL;
}

char *test_create() {
  node_t *n = node_snew("test");
  return assert_not_null(n);
}

char *test_insert() {
  node_t *n = node_snew("test");
  node_t **root = &n;

  node_sinsert(root, "teapot");
  node_sinsert(root, "tea");

  char *res = can_find(root, "test");
  return res;
}

char *test_insert_tea() {
  node_t *n = node_snew("test");
  node_t **root = &n;

  node_sinsert(root, "teapot");
  node_sinsert(root, "tea");

  char *res = can_find(root, "tea");
  return res;
}

char *test_insert_teapot() {
  node_t *n = node_snew("test");
  node_t **root = &n;

  node_sinsert(root, "teapot");
  node_sinsert(root, "tea");

  char *res = can_find(root, "teapot");
  return res;
}

char *test_insert_find_2() {
  node_t *n = node_snew("");
  node_t **root = &n;

  // replicated a failing fuzz test.
  node_sinsert(root, "a");
  node_sinsert(root, "b");

  return can_find(root, "b");
}

char *test_insert_find_3() {
  node_t *n = node_snew("t");
  node_t **root = &n;

  // replicated a failing fuzz test.
  node_sinsert(root, "a");
  node_sinsert(root, "ta");
  node_sinsert(root, "f");

  return can_find(root, "f");
}

char *test_insert_find_4() {
  node_t *n = node_snew("");
  node_t **root = &n;

  // replicated a failing fuzz test.
  node_sinsert(root, "t");
  node_sinsert(root, "ewk");
  node_sinsert(root, "hs3");
  node_sinsert(root, "hxl");

  return can_find(root, "hxl");
}

char *test_insert_find_parent() {
  node_t *n = node_snew("");
  node_t **root = &n;

  // replicated a failing fuzz test.
  node_sinsert(root, "a");
  node_sinsert(root, "ta");
  node_sinsert(root, "t");

  return can_find(root, "t");
}

char *test_insert_find() {
  node_t *n = node_snew("test");
  node_t **root = &n;

  // replicated a failing fuzz test.
  node_sinsert(root, "hs3");
  node_sinsert(root, "4r");
  node_sinsert(root, "xly");
  node_sinsert(root, "df");
  node_sinsert(root, "pcbteodjw");
  node_sinsert(root, "v0");
  node_sinsert(root, "dlr");

  char *res = can_find(root, "dlr");
  return res;
}

char *test_insert_fuzz() {
  int count = 100;

  node_t *n = node_snew("t");
  node_t **root = &n;

  int i;
  for (i = 0; i < count; i++) {
    char *r = rand_str(6);
    if (strlen(r) == 0) {
      continue;
    }

    node_sinsert(root, r);

    char *res = can_find(root, r);
    if (res != NULL) {
      printf("cannot find %s ", r);
      print_tree(*root);
      return res;
    }
  }

  return NULL;
}

void radix_tests() {
  describe("radix tree");
  test("create", test_create);
  test("insert", test_insert);
  test("insert tea", test_insert_tea);
  test("insert teapot", test_insert_teapot);
  test("insert fuzz", test_insert_fuzz);
  test("fuzz find", test_insert_find);
  test("fuzz find 2", test_insert_find_2);
  test("fuzz find 3", test_insert_find_3);
  test("fuzz find 4", test_insert_find_4);
  test("test insert find parent", test_insert_find_parent);
}
