#ifndef BLOCKS_H
#define BLOCKS_H

#include <stdbool.h>

typedef enum block_behavior_type {
  BLOCK_T_SPAWN,
  BLOCK_T_NONE,
  BLOCK_T_MOVING,
  // BLOCK_T_ROTATING,
} BlockBehaviorType;

typedef enum block_type {
  BLOCK_T_INVISIBLE,
  BLOCK_T_GRASS,
} BlockTypeEnum;

#define BLOCK_BASE                                                                                 \
  float x, y, z;                                                                                   \
  float size;                                                                                      \
  void (*update_behavior)(void *);                                                                 \
  BlockBehaviorType behavior_type;                                                                 \
  BlockTypeEnum block_type;

typedef struct block {
  BLOCK_BASE
  void (*draw)(struct block *);
} BlockBasic;

typedef struct moving_block {
  BLOCK_BASE
  float start_position_z;
  bool is_backing;
  float speed;
  float amplitude;
  void (*draw)(struct moving_block *);
} MovingBlock;

BlockBasic *create_block(BlockBasic);
void destroy_block_basic(BlockBasic *);

MovingBlock *create_moving_block(MovingBlock);
void destroy_moving_block(MovingBlock *);

void print_block(BlockBasic *b);

// Behavior functions
void update_block_moving_behavior(void *);
void update_block_rotating_behavior(void *);

#endif