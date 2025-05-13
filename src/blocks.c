#include "blocks.h"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MOVING_BLOCK_Y 0.8f
#define MIN_MOVING_BLOCK_Y 0.5f

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

void update_block_moving_behavior(MovingBlock *block) {
  float max_y = block->start_position_y + MAX_MOVING_BLOCK_Y;
  float min_y = block->start_position_y - MIN_MOVING_BLOCK_Y;

  if (block->y - block->start_position_y >= max_y) {
    block->is_backing = true;
  }

  if (block->y - block->start_position_y <= min_y) {
    block->is_backing = false;
  }

  if (!block->is_backing) {
    block->y += block->speed;
  }

  if (block->is_backing) {
    block->y -= block->speed;
  }
};

void draw_moving_block(MovingBlock *mv) {
  glPushMatrix();

  update_block_moving_behavior(mv);

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
  new_block->relative_collision_box = block.relative_collision_box;

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
  new_block->amplitude = mv.amplitude;
  new_block->speed = mv.speed;
  new_block->relative_collision_box = mv.relative_collision_box;
  new_block->is_backing = false;
  new_block->start_position_y = mv.y;

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

void update_block_rotating_behavior(void *block) {};