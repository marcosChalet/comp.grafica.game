#include "blocks.h"
#include "global.h"
#include "import-object.h"
#include "mesh-loader.h"
#include "parse-blocks.h"

#include <stdlib.h>

#define MAX_SIZE 10000
#define AWARD_PATH "./objects-to-import/DiamondSword.obj"

ImportedObject *award;

void draw_award(void *block, BlockBehaviorType type) {
  if (type == BLOCK_T_MOVING) {
    MovingBlock *tmp = block;
    draw_imported_object(award, tmp->x, tmp->y + 0.13, tmp->z, 0.003);
  } else {
    BlockBasic *tmp = block;
    draw_imported_object(award, tmp->x, tmp->y + 0.13, tmp->z, 0.003);
  }
}

void load_stage(char *path) {
  load_blocks_from_file(path);
  award = import_object(AWARD_PATH);
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
  }

  draw_award(stage_objects->tail->block, stage_objects->tail->type);
}

void free_stage() {
  destroy_global_data(get_global_obj());
}