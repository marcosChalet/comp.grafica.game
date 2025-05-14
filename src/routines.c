#include "routines.h"
#include "collision-boxes.h"
#include "global.h"

#include <math.h>
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
      .y = p->y + p->collisionYOffset,
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

CollisionDirection check_player_block_collision_direction(Player *p, BlockBasic *block) {
  AABB a = {.x = p->x,
            .y = p->y + p->collisionYOffset,
            .z = p->z,
            .depth = p->relative_collision_box->depth,
            .height = p->relative_collision_box->height,
            .width = p->relative_collision_box->width};

  AABB b = BLOCK_TO_AABB(block);

  if (!check_collision(a, b))
    return COLLISION_NONE;

  printf("colidindo! (%f, %f, %f) e (%f, %f, %f)\n", a.x, a.y, a.z, b.x, b.y, b.z);

  float dx = (a.x + a.width / 2) - (b.x + b.width / 2);
  float dy = (a.y + a.height / 2) - (b.y + b.height / 2);
  float dz = (a.z + a.depth / 2) - (b.z + b.depth / 2);

  float px = (a.width + b.width) / 2 - fabs(dx);
  float py = (a.height + b.height) / 2 - fabs(dy);
  float pz = (a.depth + b.depth) / 2 - fabs(dz);

  // O menor valor de penetração define o eixo da colisão
  if (px < py && px < pz) {
    return dx > 0 ? COLLISION_LEFT : COLLISION_RIGHT;
  } else if (py < px && py < pz) {
    return dy > 0 ? COLLISION_BOTTOM : COLLISION_TOP;
  } else {
    return dz > 0 ? COLLISION_BACK : COLLISION_FRONT;
  }
}
