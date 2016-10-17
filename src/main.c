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

char *respond(char buf[BUFFER_SIZE]) {
  cmd_t *cmd = cmd_parse(buf);

  return cmd->action;
}

int main (int argc, char *argv[]) {
  if (argc < 2) on_error("Usage: %s [port]\n", argv[0]);

  int port = atoi(argv[1]);

  serve(port, respond);
}
