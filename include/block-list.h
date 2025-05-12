#ifndef BLOCK_LIST_H
#define BLOCK_LIST_H

#include "blocks.h"

typedef struct block_wrapper {
  int id;
  void *block;
  struct block_wrapper *next;
  struct block_wrapper *prev;
} BlockWrapper;

typedef struct block_list {
  BlockWrapper *head;
  BlockWrapper *tail;
  int size;
  int max_id;
} BlockList;

BlockList *create_block_list();
void addBlockToList(BlockList *, void *);
void destroy_block_list(BlockList *);

BlockWrapper *create_block_wrapper(int id, void *block);
void destroy_block_wrapper(BlockWrapper *wrapper);

#endif