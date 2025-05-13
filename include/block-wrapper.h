#ifndef BLOCK_WRAPPER_H
#define BLOCK_WRAPPER_H

#include "blocks.h"

typedef struct block_wrapper {
  int id;
  void *block;
  struct block_wrapper *next;
  struct block_wrapper *prev;
} BlockWrapper;

BlockWrapper *create_block_wrapper(int id, void *block);
void destroy_block_wrapper(BlockWrapper *wrapper);

#endif