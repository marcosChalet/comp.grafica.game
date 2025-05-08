// platform.c
#include "platform.h"
#include <GL/glut.h>

void drawPlatform(float x, float y, float z, float scaleX, float scaleY, float scaleZ) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(scaleX, scaleY, scaleZ);
  glColor3f(0.6f, 0.4f, 0.2f);
  glutSolidCube(1.0);
  glPopMatrix();
}
