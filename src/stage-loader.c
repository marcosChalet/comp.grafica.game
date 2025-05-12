#include "blocs.h"
#include "parse-blocs.h"

#include <stdlib.h>

#define MAX_SIZE 10000

BlocGeneric **stage_blocs;

void load_stage(char *path) {
  stage_blocs = malloc(sizeof(BlocGeneric *) * MAX_SIZE);
  for (int i = 0; i < MAX_SIZE; i++) {
    stage_blocs[i] = malloc(sizeof(BlocGeneric));
  }
  load_blocs_from_file(path, stage_blocs);
}

void render_stage() {
  for (int i = 0; i < MAX_SIZE; i++) {
    if (!stage_blocs[i])
      return;
    if (stage_blocs[i]->type == BLOC_T_MOVING) {
      draw_moving_bloc((MovingBloc *)stage_blocs[i]->bloc);
    } else {
      draw_bloc((BlocBasic *)stage_blocs[i]->bloc);
    }
  }
}

void free_stage() {
  for (int i = 0; i < MAX_SIZE; i++) {
    free(stage_blocs[i]);
  }
}