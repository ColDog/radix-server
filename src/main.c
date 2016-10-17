#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "server.c"

#include "cmd.c"
#include "radix.c"

// actions
char *PUT = "PUT";
char *GET = "GET";

// tree
node_t *n;
node_t **root;

char *handle_put(cmd_t *cmd) {
  node_sinsert(root, cmd->key);
  return "200";
}

char *handle_get(cmd_t *cmd) {
  node_t *res = node_find(*root, cmd->key);
  if (res == NULL) {
    return "404";
  } else {
    return "200";
  }
}

char *respond(char buf[BUFFER_SIZE]) {
  cmd_t *cmd = cmd_parse(buf);

  if (strcmp(cmd->action, PUT) == 0) {
    return handle_put(cmd);
  } else if (strcmp(cmd->action, GET) == 0) {
    return handle_get(cmd);
  }

  return "404";
}

int main (int argc, char *argv[]) {
  if (argc < 2) on_error("Usage: %s [port]\n", argv[0]);

  int port = atoi(argv[1]);

  n = node_snew("");
  root = &n;

  printf("serving...\n");
  serve(port, respond);
}
