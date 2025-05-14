#ifndef GLOBAL_DATA
#define GLOBAL_DATA

#include "block-list.h"
#include "player.h"

typedef struct global_data {
  BlockList *block_list;
  Player *player;
} GlobalData;

GlobalData *create_global_data();
GlobalData *get_global_obj();
Player *get_global_player();
void init_global_data();
void addBlockToGlobalData(void *, BlockBehaviorType type);
void destroy_global_data(GlobalData *);
BlockWrapper *get_award_block();
void set_award_block(BlockWrapper *);

#endif