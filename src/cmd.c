#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "key.c"

#define MAX_ACTION = 10;

typedef struct cmd {
  char *action;
  char *key;
  char *value;
} cmd_t;
// CMD
// <action> <key> <value>

cmd_t *cmd_parse(char buf[BUFFER_SIZE]) {
  cmd_t *cmd = malloc(sizeof(cmd_t));

  int i = 0;
  int offset = 0;

  while (buf[i] != ' ') i++;

  cmd->action = malloc(i + 1);
  strncpy(cmd->action, buf, i);
  cmd->action[i+1] = '\0';


  offset = i + 1;
  i = 0;
  while (buf[offset + i] != ' ') i++;

  cmd->key = malloc(i + 1);
  strncpy(cmd->key, buf + offset, i);
  cmd->key[i+1] = '\0';


  offset = offset + i + 1;
  i = 0;
  while (buf[offset + i] != ' ') i++;

  cmd->value = malloc(i + 1);
  strncpy(cmd->value, buf + offset, i);
  cmd->value[i+1] = '\0';

  return cmd;
}

void cmd_free(cmd_t *cmd) {
  free(cmd->action);
  free(cmd->key);
  free(cmd->value);
  return;
}
