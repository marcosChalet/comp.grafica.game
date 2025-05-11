#include "sword.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWORD_PATH "./objects-to-import/DiamondSword.obj"

void draw_sword(Sword *sword) {

  glPushMatrix();

  glEnable(GL_NORMALIZE);
  glScalef(0.009f, 0.009f, 0.009f);
  glRotatef(40.0f, 1, -1, 0);

  GLfloat ka[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat kd[] = {0.5f, 0.5f, 0.9f, 1.0f};
  GLfloat ks[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat ns = 64.0f;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
  glMaterialf(GL_FRONT, GL_SHININESS, ns);

  draw_mesh(sword->mesh);

  glPopMatrix();
}

Sword *sword_builder() {
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