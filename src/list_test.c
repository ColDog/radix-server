#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

char *test_new_list() {
  list_t *list = list_new();
  list_push(list, "hi");
  return assert_str_equal("hi", list->head->data);
}

char *test_join_lists() {
  list_t *list = list_new();
  list_push(list, "hi");
  list_push(list, "hello");

  char *res = list_join(list, ", ");

  return assert_str_equal("hi, hello", res);
}

void list_tests() {
  describe("list");
  test("new list", test_new_list);
  test("join list", test_join_lists);
}
