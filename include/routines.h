#ifndef ROUTINES_H
#define ROUTINES_H

#include "blocks.h"
#include "collision-boxes.h"
#include "player.h"

void *check_collisions();
CollisionDirection check_player_block_collision_direction(Player *p, BlockBasic *block);

#endif