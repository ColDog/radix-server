#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.c"

char *test_parse_cmd() {
  char buf[BUFFER_SIZE] = "SET abc Value";
  cmd_t *cmd = cmd_parse(buf);
  return assert_str_equal("SET", cmd->action);
}

char *test_parse_cmd_key() {
  char buf[BUFFER_SIZE] = "SET abc Value";
  cmd_t *cmd = cmd_parse(buf);
  return assert_str_equal("abc", cmd->key);
}

char *test_parse_cmd_val() {
  char buf[BUFFER_SIZE] = "SET abc value";
  cmd_t *cmd = cmd_parse(buf);
  return assert_str_equal("value", cmd->value);
}

void cmd_tests() {
  describe("cmd");
  test("parse action", test_parse_cmd);
  test("parse key", test_parse_cmd_key);
  test("parse val", test_parse_cmd_val);
}
