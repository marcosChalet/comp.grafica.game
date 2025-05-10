#include "grassBlock.h"
#include <GL/glut.h>

GrassBlock *grassBlockPl;

void drawGrassPlatform() {
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 0.0f);
  grassBlockPl->draw(grassBlockPl);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 0.5f);
  grassBlockPl->draw(grassBlockPl);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5f, 0.0f, 0.0f);
  grassBlockPl->draw(grassBlockPl);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5f, 0.0f, 0.5f);
  grassBlockPl->draw(grassBlockPl);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5f, 0.0f, 1.0f);
  grassBlockPl->draw(grassBlockPl);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 1.0f);
  grassBlockPl->draw(grassBlockPl);
  glPopMatrix();
}

void loadPlatform() {
  grassBlockPl = grassBlockBuilder();
}
