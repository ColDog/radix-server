#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _LIST_H
#define _LIST_H

typedef struct list {
  struct list_node *head;
  struct list_node *tail;
} list_t;

typedef struct list_node {
  char *data;
  struct list_node *next;
} list_node_t;

list_t *list_new() {
  list_t *list = malloc(sizeof(list_t));
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void list_push(list_t *list, char *data) {
  list_node_t *node = malloc(sizeof(list_node_t));
  node->next = NULL;
  node->data = data;

  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
    return;
  }

  list->tail->next = node;
  list->tail = node;
}

void list_unshift(list_t *list, char *data) {
  list_node_t *node = malloc(sizeof(list_node_t));
  node->next = NULL;
  node->data = data;

  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
    return;
  }

  node->next = list->head;
  list->head = node;
}

int list_len(list_t *list) {
  list_node_t *item = list->head;
  int count = 0;
  while(item != NULL) {
    count++;
    item = item->next;
  }
  return count;
}

int list_size(list_t *list) {
  list_node_t *item = list->head;
  int count = 0;
  while(item != NULL) {
    count += strlen(item->data);
    item = item->next;
  }
  return count;
}

char *list_join(list_t *list, char *sep) {
  int sep_len = strlen(sep);

  list_node_t *item = list->head;
  int count = 0;
  int size = 0;
  while(item != NULL) {
    size += strlen(item->data);
    count++;
    item = item->next;
  }

  char *result = malloc(size + (strlen(sep) * count));

  item = list->head;
  while(item != NULL) {
    strcat(result, item->data);
    if (item->next != NULL) {
      strcat(result, sep);
    }
    item = item->next;
  }
  return result;
}

#endif
