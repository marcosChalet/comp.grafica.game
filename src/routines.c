#include "routines.h"
#include "collision-boxes.h"
#include "global.h"

#include <stdio.h>

#define BLOCK_TO_AABB(block)                                                                       \
  (AABB) {                                                                                         \
    .x = block->x, .y = block->y, .z = block->z, .depth = block->relative_collision_box->depth,    \
    .height = block->relative_collision_box->height, .width = block->relative_collision_box->width \
  }

void *check_collisions() {
  GlobalData *g = get_global_obj();
  Player *p = g->player;
  BlockWrapper *block_wrapper = g->block_list->head;

  AABB player_box = {
      .x = p->x,
      .y = p->y,
      .z = p->z,
      .depth = p->relative_collision_box->depth,
      .height = p->relative_collision_box->height,
      .width = p->relative_collision_box->width,
  };

  while (block_wrapper != NULL) {
    BlockBasic *block = block_wrapper->block;

    AABB block_box = BLOCK_TO_AABB(block);

    if (check_collision(player_box, block_box)) {
      return block;
    }

    block_wrapper = block_wrapper->next;
  }

  return NULL;
}
