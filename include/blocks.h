#ifndef BLOCKS_H
#define BLOCKS_H

#include "collision-boxes.h"

#include <GL/glut.h>
#include <stdbool.h>

typedef enum block_behavior_type {
  BLOCK_T_SPAWN,
  BLOCK_T_NONE,
  BLOCK_T_MOVING,
} BlockBehaviorType;

typedef enum block_type {
  BLOCK_T_INVISIBLE,
  BLOCK_T_GRASS,
  BLOCK_T_VICTORY,
  BLOCK_T_WOOD,
} BlockTypeEnum;

#define BLOCK_BASE                                                                                 \
  float x, y, z;                                                                                   \
  float size;                                                                                      \
  RelativeCollisionBox *relative_collision_box;                                                    \
  BlockBehaviorType behavior_type;                                                                 \
  BlockTypeEnum block_type;

typedef struct block {
  BLOCK_BASE
} BlockBasic;

typedef struct moving_block {
  BLOCK_BASE
  float start_position_y;
  bool is_backing;
  float speed;
  float amplitude;
} MovingBlock;

BlockBasic *create_block(BlockBasic);
void destroy_block_basic(BlockBasic *);

MovingBlock *create_moving_block(MovingBlock);
void destroy_moving_block(MovingBlock *);

void print_block(BlockBasic *b);

void load_textures();
void draw_block(BlockBasic *b);
void draw_moving_block(MovingBlock *mv);

// Behavior functions
void update_block_rotating_behavior(void *);

#endif