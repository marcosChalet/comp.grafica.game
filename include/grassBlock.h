#ifndef GRASS_BLOCK_H
#define GRASS_BLOCK_H

#include "meshLoader.h"

typedef struct grassBlock {
  Mesh mesh;
  void (*draw)(struct grassBlock *grassBlock);
} GrassBlock;

GrassBlock *grassBlockBuilder();

#endif