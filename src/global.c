#include "global.h"

#include <stdio.h>
#include <stdlib.h>

GlobalData *global_data;
BlockWrapper *award_block;

GlobalData *create_global_data() {
  GlobalData *data = (GlobalData *)malloc(sizeof(GlobalData));
  if (data == NULL) {
    fprintf(stderr, "Failed to allocate memory for GlobalData\n");
    exit(EXIT_FAILURE);
  }

  printf("creating block list\n");
  data->block_list = create_block_list();
  printf("creating player\n");
  data->player = create_player();

  printf("global data object created\n");

  return data;
}

GlobalData *get_global_obj() {
  return global_data;
}

Player *get_global_player() {
  if (global_data)
    return global_data->player;
  return NULL;
}

void init_global_data() {
  global_data = create_global_data();
}

void addBlockToGlobalData(void *block, BlockBehaviorType type) {
  addBlockToList(global_data->block_list, block, type);
}

void destroy_global_data(GlobalData *data) {
  if (data == NULL) {
    return;
  }

  destroy_block_list(data->block_list);
  free(data);
}

void set_award_block(BlockWrapper *b) {
  award_block = b;
}

BlockWrapper *get_award_block() {
  return award_block;
}
