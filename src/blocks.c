#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "blocks.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_MOVING_BLOCK_Y 0.8f
#define MIN_MOVING_BLOCK_Y -0.0f

#define BLOCK_GRASS_TOP "./objects-to-import/azalea_top.png"
#define BLOCK_GRASS_SIDE "./objects-to-import/grass_block_side.png"
#define BLOCK_DIRT "./objects-to-import/dirt.png"
#define BLOCK_WOOD "./objects-to-import/acacia_planks.png"
#define BLOCK_VICTORY "./objects-to-import/crying_obsidian.png"
static GLuint side_texture;
static GLuint dirt_texture;
static GLuint grass_texture;
static GLuint block_victory_texture;
static GLuint frosted_ice;

GLuint load_texture(const char *filename) {
  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
  if (!data) {
    printf("Erro ao carregar imagem: %s\n", filename);
    return 0;
  }

  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);

  return tex;
}

void load_textures() {
  side_texture = load_texture(BLOCK_GRASS_SIDE);
  dirt_texture = load_texture(BLOCK_DIRT);
  grass_texture = load_texture(BLOCK_GRASS_TOP);
  block_victory_texture = load_texture(BLOCK_VICTORY);
  frosted_ice = load_texture(BLOCK_WOOD);

  if (!side_texture || !dirt_texture || !grass_texture || !block_victory_texture || !frosted_ice) {
    printf("Falha ao carregar textura.\n");
  }
}

void draw_grass_textured_cube(float size) {
  float half = size / 2.0f;
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);

  glBindTexture(GL_TEXTURE_2D, grass_texture);
  glBegin(GL_QUADS);
  // Cima
  glTexCoord2f(0, 0);
  glVertex3f(-half, half, half);
  glTexCoord2f(1, 0);
  glVertex3f(half, half, half);
  glTexCoord2f(1, 1);
  glVertex3f(half, half, -half);
  glTexCoord2f(0, 1);
  glVertex3f(-half, half, -half);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, dirt_texture);
  glBegin(GL_QUADS);
  // Baixo
  glTexCoord2f(0, 0);
  glVertex3f(-half, -half, -half);
  glTexCoord2f(1, 0);
  glVertex3f(half, -half, -half);
  glTexCoord2f(1, 1);
  glVertex3f(half, -half, half);
  glTexCoord2f(0, 1);
  glVertex3f(-half, -half, half);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, side_texture);
  glBegin(GL_QUADS);
  // Frente
  glTexCoord2f(0, 0);
  glVertex3f(-half, -half, half);
  glTexCoord2f(1, 0);
  glVertex3f(half, -half, half);
  glTexCoord2f(1, 1);
  glVertex3f(half, half, half);
  glTexCoord2f(0, 1);
  glVertex3f(-half, half, half);

  // Trás
  glTexCoord2f(0, 0);
  glVertex3f(half, -half, -half);
  glTexCoord2f(1, 0);
  glVertex3f(-half, -half, -half);
  glTexCoord2f(1, 1);
  glVertex3f(-half, half, -half);
  glTexCoord2f(0, 1);
  glVertex3f(half, half, -half);

  // Esquerda
  glTexCoord2f(0, 0);
  glVertex3f(-half, -half, -half);
  glTexCoord2f(1, 0);
  glVertex3f(-half, -half, half);
  glTexCoord2f(1, 1);
  glVertex3f(-half, half, half);
  glTexCoord2f(0, 1);
  glVertex3f(-half, half, -half);

  // Direita
  glTexCoord2f(0, 0);
  glVertex3f(half, -half, half);
  glTexCoord2f(1, 0);
  glVertex3f(half, -half, -half);
  glTexCoord2f(1, 1);
  glVertex3f(half, half, -half);
  glTexCoord2f(0, 1);
  glVertex3f(half, half, half);
  glEnd();

  glEnable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
}

void draw_uniform_textured_cube(float size, GLuint texture) {
  float half = size / 2.0f;
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);

  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  // Cima
  glTexCoord2f(0, 0);
  glVertex3f(-half, half, half);
  glTexCoord2f(1, 0);
  glVertex3f(half, half, half);
  glTexCoord2f(1, 1);
  glVertex3f(half, half, -half);
  glTexCoord2f(0, 1);
  glVertex3f(-half, half, -half);

  // Baixo
  glTexCoord2f(0, 0);
  glVertex3f(-half, -half, -half);
  glTexCoord2f(1, 0);
  glVertex3f(half, -half, -half);
  glTexCoord2f(1, 1);
  glVertex3f(half, -half, half);
  glTexCoord2f(0, 1);
  glVertex3f(-half, -half, half);

  // Frente
  glTexCoord2f(0, 0);
  glVertex3f(-half, -half, half);
  glTexCoord2f(1, 0);
  glVertex3f(half, -half, half);
  glTexCoord2f(1, 1);
  glVertex3f(half, half, half);
  glTexCoord2f(0, 1);
  glVertex3f(-half, half, half);

  // Trás
  glTexCoord2f(0, 0);
  glVertex3f(half, -half, -half);
  glTexCoord2f(1, 0);
  glVertex3f(-half, -half, -half);
  glTexCoord2f(1, 1);
  glVertex3f(-half, half, -half);
  glTexCoord2f(0, 1);
  glVertex3f(half, half, -half);

  // Esquerda
  glTexCoord2f(0, 0);
  glVertex3f(-half, -half, -half);
  glTexCoord2f(1, 0);
  glVertex3f(-half, -half, half);
  glTexCoord2f(1, 1);
  glVertex3f(-half, half, half);
  glTexCoord2f(0, 1);
  glVertex3f(-half, half, -half);

  // Direita
  glTexCoord2f(0, 0);
  glVertex3f(half, -half, half);
  glTexCoord2f(1, 0);
  glVertex3f(half, -half, -half);
  glTexCoord2f(1, 1);
  glVertex3f(half, half, -half);
  glTexCoord2f(0, 1);
  glVertex3f(half, half, half);
  glEnd();

  glEnable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
}

void draw_block(BlockBasic *b) {
  glPushMatrix();
  glTranslatef(b->x, b->y, b->z);
  if (b->block_type == BLOCK_T_VICTORY) {
    draw_uniform_textured_cube(b->size, block_victory_texture);
  } else if (b->block_type == BLOCK_T_WOOD) {
    draw_uniform_textured_cube(b->size, frosted_ice);
  } else {
    draw_grass_textured_cube(b->size);
  }
  glPopMatrix();
}

void update_block_moving_behavior(MovingBlock *block) {
  float max_y = block->start_position_y + MAX_MOVING_BLOCK_Y;
  float min_y = block->start_position_y + MIN_MOVING_BLOCK_Y;

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
  glTranslatef(mv->x, mv->y, mv->z);
  if (mv->block_type == BLOCK_T_VICTORY) {
    draw_uniform_textured_cube(mv->size, block_victory_texture);
  } else if (mv->block_type == BLOCK_T_WOOD) {
    draw_uniform_textured_cube(mv->size, frosted_ice);
  } else {
    draw_grass_textured_cube(mv->size);
  }
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