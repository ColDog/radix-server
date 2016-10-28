#include <stdio.h>
#include <stdlib.h>
#include "src/test.c"
#include "src/radix_test.c"
#include "src/cmd_test.c"
#include "src/list_test.c"
#include "src/mem_pool_test.c"
#include "src/ds_test.c"

void tests() {
  // radix_tests();
  // cmd_tests();
  // list_tests();
  mem_pool_tests();
  ds_tests();
}

int main() {
  return test_runner(tests);
}
