#include "blocks.h"
#include "global.h"
#include "parse-blocks.h"

#include <stdlib.h>

#define MAX_SIZE 10000

void load_stage(char *path) {
  load_blocks_from_file(path);
}

void render_stage() {
  BlockList *stage_objects = get_global_obj()->block_list;
  BlockWrapper *aux = stage_objects->head;
  for (int i = 0; i < stage_objects->size; i++) {

    if (aux->type == BLOCK_T_MOVING) {
      draw_moving_block((MovingBlock *)aux->block);
    } else {
      draw_block((BlockBasic *)aux->block);
    }

    aux = aux->next;

    //   if (!stage_blocks[i])
    //     return;
    //   if (stage_blocks[i]->type == BLOCK_T_MOVING) {
    //     draw_moving_block((MovingBlock *)stage_blocks[i]->block);
    //   } else {
    //     draw_block((BlockBasic *)stage_blocks[i]->block);
    //   }
  }
}

void free_stage() {
  destroy_global_data(get_global_obj());
}