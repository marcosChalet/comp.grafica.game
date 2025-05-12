#include "block-list.h"

#include <stdio.h>
#include <stdlib.h>

BlockkList *create_block_list() {
  BlockkList *list = (BlockkList *)malloc(sizeof(BlockkList));
  if (list == NULL) {
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  list->max_id = 0;

  return list;
}

void addBlockkToList(BlockkList *list, void *block) {
  if (list == NULL || block == NULL) {
    return;
  }

  BlockkWrapper *wrapper = create_block_wrapper(++list->max_id, block);
  if (wrapper == NULL) {
    return;
  }

  if (list->head == NULL) {
    list->head = wrapper;
    list->tail = wrapper;
  } else {
    list->tail->next = wrapper;
    list->tail = wrapper;
  }

  list->size++;
}

void destroy_block_list(BlockkList *block_list) {
  if (block_list == NULL) {
    return;
  }

  BlockkWrapper *current = block_list->head;
  while (current != NULL) {
    BlockkWrapper *next = current->next;
    destroy_block_wrapper(current);
    current = next;
  }

  free(block_list);
}

BlockkWrapper *create_block_wrapper(int id, void *block) {
  BlockkWrapper *wrapper = (BlockkWrapper *)malloc(sizeof(BlockkWrapper));
  if (wrapper == NULL) {
    return NULL;
  }
  wrapper->id = id;
  wrapper->block = block;

  return wrapper;
}

void destroy_block_wrapper(BlockkWrapper *wrapper) {
  if (wrapper != NULL) {
    free(wrapper);
  }
}
