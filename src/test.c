#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_count = 0;
int fail_count = 0;
int pass_count = 0;
char *matches = NULL;

typedef char * (*test_t)();
typedef void (*tests_t)();

char *assert_int_equal(int expected, int actual) {
  if (expected != actual) {
    printf("\n    expected = %d\n    actual = %d\n", expected, actual);
    return "values do not match";
  }
  return NULL;
}

char *assert_not_int_equal(int expected, int actual) {
  if (expected == actual) {
    printf("\n    expected = %d\n    actual = %d\n", expected, actual);
    return "values do match";
  }
  return NULL;
}

char *assert_str_equal(char *expected, char *actual) {
  if (strcmp(expected, actual) != 0) {
    printf("\n    expected = %s\n    actual = %s\n", expected, actual);
    return "values do not match";
  }
  return NULL;
}

char *assert_not_null_m(void *value, char *msg) {
  if (value == NULL) {
    return msg;
  } else {
    return NULL;
  }
}

char *assert_not_null(void *value) {
  if (value == NULL) {
    return "Value is null";
  } else {
    return NULL;
  }
}

void test(char *desc, test_t test_func) {
  if (matches != NULL && desc != matches) return;

  printf("  %d: [test] %s ... ", test_count, desc);
  char *res = test_func();
  if (res == NULL) {
    printf("PASS\n");
    pass_count++;
  } else {
    printf("FAIL %s\n", res);
    fail_count++;
  }
  test_count++;
}

void describe(char *name) {
  printf("\n\n%s\n", name);
}

int finish() {
  printf("\n\n------------------\n%d tests run %d failing, %d passing\n",
    test_count, fail_count, pass_count);
  return fail_count == 0 ? 0 : 137;
}

int test_runner(tests_t tests) {
  tests();
  return finish();
}
