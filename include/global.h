#ifndef GLOBAL_DATA
#define GLOBAL_DATA

#include "block-list.h"

typedef struct global_data {
  BlockkList *block_list;
} GlobalData;

GlobalData *create_global_data();
GlobalData *get_global_obj();
void init_global_data();
void addBlockkToGlobalData(void *);
void destroy_global_data(GlobalData *);

#endif