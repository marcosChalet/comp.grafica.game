#include "global.h"

#include <stdio.h>
#include <stdlib.h>

GlobalData *global_data;

GlobalData *create_global_data() {
  GlobalData *data = (GlobalData *)malloc(sizeof(GlobalData));
  if (data == NULL) {
    fprintf(stderr, "Failed to allocate memory for GlobalData\n");
    exit(EXIT_FAILURE);
  }

  data->block_list = create_block_list();

  return data;
}

GlobalData *get_global_obj() {
  return global_data;
}

void init_global_data() {
  global_data = create_global_data();
}

void addBlockkToGlobalData(void *block) {
  addBlockkToList(global_data->block_list, block);
}

void destroy_global_data(GlobalData *data) {
  if (data == NULL) {
    return;
  }

  destroy_block_list(data->block_list);
  free(data);
}
