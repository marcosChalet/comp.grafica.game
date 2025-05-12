#include "block-list.h"

#include <stdio.h>
#include <stdlib.h>

BlockList *create_block_list() {
  BlockList *list = (BlockList *)malloc(sizeof(BlockList));
  if (list == NULL) {
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  list->max_id = 0;

  return list;
}

void addBlockToList(BlockList *list, void *block) {
  if (list == NULL || block == NULL) {
    return;
  }

  BlockWrapper *wrapper = create_block_wrapper(++list->max_id, block);
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

void destroy_block_list(BlockList *block_list) {
  if (block_list == NULL) {
    return;
  }

  BlockWrapper *current = block_list->head;
  while (current != NULL) {
    BlockWrapper *next = current->next;
    destroy_block_wrapper(current);
    current = next;
  }

  free(block_list);
}

BlockWrapper *create_block_wrapper(int id, void *block) {
  BlockWrapper *wrapper = (BlockWrapper *)malloc(sizeof(BlockWrapper));
  if (wrapper == NULL) {
    return NULL;
  }
  wrapper->id = id;
  wrapper->block = block;

  return wrapper;
}

void destroy_block_wrapper(BlockWrapper *wrapper) {
  if (wrapper != NULL) {
    free(wrapper);
  }
}
