#include "parse-blocks.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

BlockBehaviorType parse_behavior(const char *str) {
  if (strcmp(str, "BLOCK_T_SPAWN") == 0)
    return BLOCK_T_SPAWN;
  if (strcmp(str, "BLOCK_T_NONE") == 0)
    return BLOCK_T_NONE;
  if (strcmp(str, "BLOCK_T_MOVING") == 0)
    return BLOCK_T_MOVING;
  return -1;
}

BlockTypeEnum parse_block_type(const char *str) {
  if (strcmp(str, "BLOCK_T_INVISIBLE") == 0)
    return BLOCK_T_INVISIBLE;
  if (strcmp(str, "BLOCK_T_GRASS") == 0)
    return BLOCK_T_GRASS;
  return -1;
}

void load_blocks_from_file(const char *filename) {
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

    BlockBehaviorType behavior = parse_behavior(behavior_str);
    BlockTypeEnum block_type = parse_block_type(type_str);

    if (behavior == BLOCK_T_MOVING) {
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

      MovingBlock temp = {.x = x,
                          .y = y,
                          .z = z,
                          .size = size,
                          .update_behavior = &update_block_moving_behavior,
                          .behavior_type = behavior,
                          .block_type = block_type,
                          .speed = speed,
                          .amplitude = amplitude};

      MovingBlock *mb = create_moving_block(temp);
      addBlockToGlobalData(mb, behavior);
      print_block((BlockBasic *)mb); // imprime para debug

    } else if (behavior == BLOCK_T_SPAWN) {
      init_player(x, y, z, get_global_player());
    } else {
      char *size_str = strstr(line, "size=");

      if (size_str)
        size = atof(size_str + 5);

      BlockBasic temp = {.x = x,
                         .y = y,
                         .z = z,
                         .size = size,
                         .update_behavior = NULL,
                         .behavior_type = behavior,
                         .block_type = block_type};

      BlockBasic *b = create_block(temp);
      addBlockToGlobalData(b, behavior);
      print_block(b); // imprime para debug
    }
  }

  fclose(file);
}
