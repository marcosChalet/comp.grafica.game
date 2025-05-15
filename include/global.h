#ifndef GLOBAL_DATA
#define GLOBAL_DATA

#include "block-list.h"
#include "player.h"

typedef struct spawn_point {
  float x, y, z;
} SpawnPoint;

typedef struct global_data {
  BlockList *block_list;
  Player *player;
  SpawnPoint *spawn_point;
} GlobalData;

GlobalData *create_global_data();
GlobalData *get_global_obj();
Player *get_global_player();
void init_global_data();
SpawnPoint *get_spawn_point();
void set_spawn_point(float x, float y, float z);
void addBlockToGlobalData(void *, BlockBehaviorType type);
void destroy_global_data(GlobalData *);
BlockWrapper *get_award_block();
void set_award_block(BlockWrapper *);

#endif