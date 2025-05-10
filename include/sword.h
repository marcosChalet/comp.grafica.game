#ifndef SWORD_H
#define SWORD_H

#include "meshLoader.h"

typedef struct sword {
  Mesh mesh;
  void (*draw)(struct sword *sword);
} Sword;

Sword *swordBuilder();

#endif