#ifndef SWORD_H
#ifndef SWORD_H

#include "mesh-loader.h"

typedef struct sword {
  Mesh mesh;
  void (*draw)(struct sword *sword);
} Sword;

void draw_sword(Sword *sword);
Sword *sword_builder();

#endif