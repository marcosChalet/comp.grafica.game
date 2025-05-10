#ifndef STEVE_H
#define STEVE_H

#include "meshLoader.h"

typedef struct steve {
  Mesh mesh;
  void (*draw)(struct steve *steve);
} Steve;

Steve *steveBuilder(char *path);

#endif