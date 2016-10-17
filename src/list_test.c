#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

char *test_new_list() {
  list_t *list = list_new();
  list_add(list, "hi");
  return assert_str_equal("hi", list->head->data);
}

void list_tests() {
  describe("list");
  test("new list", test_new_list);
}
