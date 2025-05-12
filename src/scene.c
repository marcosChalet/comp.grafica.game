#include "platform.h"
#include "player.h"
#include <GL/glut.h>

void drawScene() {

  // scene sample

  update_player_position();

  // drawPlatform(6.0f, 0.0f, 0.0f, 4.0f, 0.2f, 3.0f);

  // chão
  glColor3f(0.5f, 0.5f, 0.5f);
  glBegin(GL_QUADS);
  glVertex3f(-20.0f, -1.0f, 20.0f);
  glVertex3f(20.0f, -1.0f, 20.0f);
  glVertex3f(20.0f, -1.0f, -20.0f);
  glVertex3f(-20.0f, -1.0f, -20.0f);
  glEnd();

  // blocko 1
  // glPushMatrix();
  // glTranslatef(0.0f, -1.5f + (2.0f / 2.0f), -5.0f); // y = -0.5
  // glScalef(2.0f, 2.0f, 2.0f);
  // glColor3f(0.8f, 0.2f, 0.2f);
  // glutSolidCube(1.0);
  // glPopMatrix();

  // // blocko 2
  // glPushMatrix();
  // glTranslatef(3.0f, -1.5f + (2.5f / 2.0f), -8.0f); // y = -0.25
  // glScalef(2.5f, 2.5f, 2.5f);
  // glColor3f(0.2f, 0.2f, 0.8f);
  // glutSolidCube(1.0);
  // glPopMatrix();

  // // blocko 3
  // glPushMatrix();
  // glTranslatef(-4.0f, -1.5f + (1.0f / 2.0f), -12.0f); // y = -1.0
  // glScalef(3.0f, 1.0f, 3.0f);
  // glColor3f(0.2f, 0.8f, 0.2f);
  // glutSolidCube(1.0);
  // glPopMatrix();
}
