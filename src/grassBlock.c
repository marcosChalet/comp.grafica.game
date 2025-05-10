#include "grassBlock.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRASS_BLOCK_PATH "./data/GrassBlock.obj"

void drawGrassBlock(GrassBlock *grassBlock) {

  glPushMatrix(); // Salva o estado atual da transformação e do material
  glEnable(GL_NORMALIZE);
  // glScalef(0.05f, 0.05f, 0.05f);
  glScalef(0.17f, 0.17f, 0.17f);
  // glRotatef(5.0f, 1, 0, 0);
  // glScalef(0.20f, 0.20f, 0.20f);

  // --- DEFINIÇÃO DO MATERIAL ---
  GLfloat ka[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat kd[] = {0.5f, 0.3f, 0.0f, 1.0f}; // cor principal (marrom dourado)
  GLfloat ks[] = {1.0f, 1.0f, 1.0f, 1.0f}; // brilho
  GLfloat ns = 24.0f;                      // intensidade do brilho

  // glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
  // glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
  // glMaterialf(GL_FRONT, GL_SHININESS, ns);

  // --- FIM DO MATERIAL ---

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, grassBlock->mesh.vertices);

  if (grassBlock->mesh.normals) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, grassBlock->mesh.normals);
  }

  if (grassBlock->mesh.texcoords) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, grassBlock->mesh.texcoords);
  }

  glDrawArrays(GL_TRIANGLES, 0, grassBlock->mesh.num_triangles * 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glPopMatrix(); // Restaura o estado anterior da transformação e do material
}

GrassBlock *grassBlockBuilder() {
  GrassBlock *newGrassBlock = malloc(sizeof(GrassBlock));
  if (!newGrassBlock) {
    perror("Steve builder memory allocation error");
    return NULL;
  }

  memset(&newGrassBlock->mesh, 0, sizeof(Mesh));
  load_mesh(&newGrassBlock->mesh, GRASS_BLOCK_PATH);
  newGrassBlock->draw = &drawGrassBlock;

  return newGrassBlock;
}