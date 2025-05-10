#include "sword.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWORD_PATH "./data/DiamondSword.obj"

void drawSword(Sword *sword) {

  glPushMatrix(); // Salva o estado atual da transformação e do material

  glScalef(0.009f, 0.009f, 0.009f);
  glRotatef(40.0f, 1, -1, 0);
  glEnable(GL_NORMALIZE);

  // --- DEFINIÇÃO DO MATERIAL ---
  GLfloat ka[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat kd[] = {0.5f, 0.5f, 0.9f, 1.0f}; // cor principal (azul)
  GLfloat ks[] = {1.0f, 1.0f, 1.0f, 1.0f}; // brilho
  GLfloat ns = 64.0f;                      // intensidade do brilho

  // glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
  // glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
  // glMaterialf(GL_FRONT, GL_SHININESS, ns);

  // --- FIM DO MATERIAL ---

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, sword->mesh.vertices);

  if (sword->mesh.normals) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, sword->mesh.normals);
  }

  if (sword->mesh.texcoords) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, sword->mesh.texcoords);
  }

  glDrawArrays(GL_TRIANGLES, 0, sword->mesh.num_triangles * 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glPopMatrix(); // Restaura o estado anterior da transformação e do material
}

Sword *swordBuilder() {
  Sword *newSword = malloc(sizeof(Sword));
  if (!newSword) {
    perror("Sword memory allocation error");
    return NULL;
  }

  memset(&newSword->mesh, 0, sizeof(Mesh));
  load_mesh(&newSword->mesh, SWORD_PATH);
  newSword->draw = &drawSword;

  return newSword;
}