#ifndef GLOBAL_DATA
#define GLOBAL_DATA

#include "block-list.h"

typedef struct global_data {
  BlockList *block_list;
} GlobalData;

GlobalData *create_global_data();
GlobalData *get_global_obj();
void init_global_data();
void addBlockToGlobalData(void *, BlockBehaviorType type);
void destroy_global_data(GlobalData *);

#endif