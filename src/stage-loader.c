#include "blocks.h"
#include "parse-blocks.h"

#include <stdlib.h>

#define MAX_SIZE 10000

BlockGeneric **stage_blocks;

void load_stage(char *path) {
  stage_blocks = malloc(sizeof(BlockGeneric *) * MAX_SIZE);
  for (int i = 0; i < MAX_SIZE; i++) {
    stage_blocks[i] = malloc(sizeof(BlockGeneric));
  }
  load_blocks_from_file(path, stage_blocks);
}

void render_stage() {
  for (int i = 0; i < MAX_SIZE; i++) {
    if (!stage_blocks[i])
      return;
    if (stage_blocks[i]->type == BLOCK_T_MOVING) {
      draw_moving_block((MovingBlock *)stage_blocks[i]->block);
    } else {
      draw_block((BlockBasic *)stage_blocks[i]->block);
    }
  }
}

void free_stage() {
  for (int i = 0; i < MAX_SIZE; i++) {
    free(stage_blocks[i]);
  }
}