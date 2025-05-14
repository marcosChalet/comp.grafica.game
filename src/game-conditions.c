#include "game-conditions.h"
#include "blocks.h"
#include "collision-boxes.h"
#include "global.h"
#include "parse-blocks.h"

#include <stdio.h>

#define MIN_Y_PLAYER -5
static bool is_winner = false;

bool is_dead() {
  Player *player = get_global_player();
  if (player->y <= MIN_Y_PLAYER) {
    return true;
  }
  return false;
}

void respawn_player() {
  Player *player = get_global_player();
  player->gazeDirectionY = -1.9;
  player->x = 0;
  player->y = 20;
  player->z = 0.5;
}

void check_victory() {
  Player *player = get_global_player();
  BlockWrapper *award_block = get_award_block();
  bool victory_status = false;

  if (is_winner) {
    return;
  }

  RelativeCollisionBox *relative_player = create_relative_collision_box(0.09, 0.18, 0.09);
  RelativeCollisionBox *award = create_relative_collision_box(0.09, 0.18, 0.09);

  AABB player_box = {
      .x = player->x,
      .y = player->y + player->collisionYOffset,
      .z = player->z,
      .depth = player->relative_collision_box->depth,
      .height = player->relative_collision_box->height,
      .width = player->relative_collision_box->width,
  };

  if (award_block->type == BLOCK_T_MOVING) {
    AABB award_box = {
        .x = ((MovingBlock *)award_block->block)->x,
        .y = ((MovingBlock *)award_block->block)->y,
        .z = ((MovingBlock *)award_block->block)->z,
        .depth = award->depth,
        .height = award->height,
        .width = award->width,
    };

    victory_status = check_collision(player_box, award_box);
  } else {
    AABB award_box = {
        .x = ((BlockBasic *)award_block->block)->x,
        .y = ((BlockBasic *)award_block->block)->y,
        .z = ((BlockBasic *)award_block->block)->z,
        .depth = award->depth,
        .height = award->height,
        .width = award->width,
    };

    victory_status = check_collision(player_box, award_box);
  }

  if (victory_status) {
    load_blocks_from_file("./3d-objects/victory.conf");
    is_winner = true;
  }
}