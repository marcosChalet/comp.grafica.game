#include "parse-blocs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
int num_blocs = 0;

BlocBehaviorType parse_behavior(const char *str) {
  if (strcmp(str, "BLOC_T_SPAWN") == 0)
    return BLOC_T_SPAWN;
  if (strcmp(str, "BLOC_T_NONE") == 0)
    return BLOC_T_NONE;
  if (strcmp(str, "BLOC_T_MOVING") == 0)
    return BLOC_T_MOVING;
  return -1;
}

BlocTypeEnum parse_bloc_type(const char *str) {
  if (strcmp(str, "BLOC_T_INVISIBLE") == 0)
    return BLOC_T_INVISIBLE;
  if (strcmp(str, "BLOC_T_GRASS") == 0)
    return BLOC_T_GRASS;
  return -1;
}

void load_blocs_from_file(const char *filename, BlocGeneric **blocs) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Erro ao abrir arquivo");
    return;
  }

  char line[MAX_LINE];
  while (fgets(line, sizeof(line), file)) {
    float x, y, z;
    char behavior_str[64], type_str[64];
    float speed = 0, amplitude = 0;
    int is_moving = 0;
    float size;

    sscanf(line, "%f %f %f %s %s", &x, &y, &z, behavior_str, type_str);

    BlocBehaviorType behavior = parse_behavior(behavior_str);
    BlocTypeEnum bloc_type = parse_bloc_type(type_str);

    if (behavior == BLOC_T_MOVING) {
      is_moving = 1;
      char *size_str = strstr(line, "size=");
      char *speed_str = strstr(line, "speed=");
      char *amp_str = strstr(line, "amplitude=");

      if (size_str)
        size = atof(size_str + 5);
      if (speed_str)
        speed = atof(speed_str + 6);
      if (amp_str)
        amplitude = atof(amp_str + 10);

      MovingBloc temp = {.x = x,
                         .y = y,
                         .z = z,
                         .size = size,
                         .update_behavior = &update_bloc_moving_behavior,
                         .behavior_type = behavior,
                         .bloc_type = bloc_type,
                         .speed = speed,
                         .amplitude = amplitude};

      MovingBloc *mb = create_moving_bloc(temp);
      blocs[num_blocs]->bloc = mb;
      blocs[num_blocs++]->type = behavior;
      // blocs[num_blocs] = NULL;
      print_bloc((BlocBasic *)mb); // imprime para debug

    } else {
      char *size_str = strstr(line, "size=");

      if (size_str)
        size = atof(size_str + 5);

      BlocBasic temp = {.x = x,
                        .y = y,
                        .z = z,
                        .size = size,
                        .update_behavior = NULL,
                        .behavior_type = behavior,
                        .bloc_type = bloc_type};

      BlocBasic *b = create_bloc(temp);
      blocs[num_blocs]->bloc = b;
      blocs[num_blocs++]->type = behavior;

      print_bloc(b); // imprime para debug
    }
  }

  blocs[num_blocs] = NULL;
  fclose(file);
}
