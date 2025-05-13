#include "blocks.h"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void draw_block(BlockBasic *b) {
  glPushMatrix();

  GLfloat ka[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat kd[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat ks[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat ns = 64.0f;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
  glMaterialf(GL_FRONT, GL_SHININESS, ns);

  // glColor3f(0.2, 0.9, 0.2);
  glTranslatef(b->x, b->y, b->z);
  glutSolidCube(b->size);
  glPopMatrix();
}

void draw_moving_block(MovingBlock *mv) {
  glPushMatrix();

  GLfloat ka[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat kd[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat ks[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat ns = 64.0f;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
  glMaterialf(GL_FRONT, GL_SHININESS, ns);

  // glColor3f(0.2, 0.9, 0.2);
  glTranslatef(mv->x, mv->y, mv->z);
  glutSolidCube(mv->size);
  glPopMatrix();
}

BlockBasic *create_block(BlockBasic block) {
  BlockBasic *new_block = (BlockBasic *)malloc(sizeof(BlockBasic));

  new_block->x = block.x;
  new_block->y = block.y;
  new_block->z = block.z;
  new_block->size = block.size;
  new_block->block_type = block.block_type;
  new_block->behavior_type = block.behavior_type;
  new_block->update_behavior = block.update_behavior;

  return new_block;
}

void destroy_block_basic(BlockBasic *b) {
  free(b);
}

MovingBlock *create_moving_block(MovingBlock mv) {
  MovingBlock *new_block = (MovingBlock *)malloc(sizeof(MovingBlock));

  new_block->x = mv.x;
  new_block->y = mv.y;
  new_block->z = mv.z;
  new_block->size = mv.size;
  new_block->block_type = mv.block_type;
  new_block->behavior_type = mv.behavior_type;
  new_block->update_behavior = mv.update_behavior;
  new_block->amplitude = mv.amplitude;
  new_block->speed = mv.speed;

  return new_block;
}

void destroy_moving_block(MovingBlock *mb) {
  free(mb);
}

void print_block(BlockBasic *b) {
  if (!b) {
    printf("Blocko nulo.\n");
    return;
  }

  printf("Posição: (%.2f, %.2f, %.2f)\n", b->x, b->y, b->z);

  switch (b->block_type) {
  case BLOCK_T_INVISIBLE:
    printf("Tipo de blocko: INVISÍVEL\n");
    break;
  case BLOCK_T_GRASS:
    printf("Tipo de blocko: GRAMA\n");
    break;
  default:
    printf("Tipo de blocko: DESCONHECIDO\n");
  }

  switch (b->behavior_type) {
  case BLOCK_T_SPAWN:
    printf("Comportamento: SPAWN\n");
    break;
  case BLOCK_T_NONE:
    printf("Comportamento: NENHUM\n");
    break;
  case BLOCK_T_MOVING:
    printf("Comportamento: MÓVEL\n");
    // Cast para MovingBlock
    {
      MovingBlock *mb = (MovingBlock *)b;
      printf("  Velocidade: %.2f\n", mb->speed);
      printf("  Amplitude: %.2f\n", mb->amplitude);
    }
    break;
  default:
    printf("Comportamento: DESCONHECIDO\n");
  }

  printf("\n");
}

void update_block_moving_behavior(void *block) {};
void update_block_rotating_behavior(void *block) {};