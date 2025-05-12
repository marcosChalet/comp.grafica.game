#ifndef BLOCKK_LIST_H
#define BLOCKK_LIST_H

#include "blocks.h"

typedef struct block_wrapper {
  int id;
  void *block;
  struct block_wrapper *next;
  struct block_wrapper *prev;
} BlockkWrapper;

typedef struct block_list {
  BlockkWrapper *head;
  BlockkWrapper *tail;
  int size;
  int max_id;
} BlockkList;

BlockkList *create_block_list();
void addBlockkToList(BlockkList *, void *);
void destroy_block_list(BlockkList *);

BlockkWrapper *create_block_wrapper(int id, void *block);
void destroy_block_wrapper(BlockkWrapper *wrapper);

#endif