#include <stdio.h>
#include <stdlib.h>
#include "src/test.c"
#include "src/radix_test.c"
#include "src/cmd_test.c"

void tests() {
  radix_tests();
  cmd_tests();
  list_tests();
}

int main() {
  return test_runner(tests);
}
