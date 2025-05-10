#include "grassPlatform.h"
#include <GL/glut.h>

void drawFloor(float x, float y, float z, float scaleX, float scaleY, float scaleZ) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(scaleX, scaleY, scaleZ);

  // Definindo um material opaco
  GLfloat ka[] = {0.1f, 0.1f, 0.1f, 1.0f}; // ambiente com cor escura (não reflete muita luz)
  GLfloat kd[] = {0.6f, 0.6f, 0.6f, 1.0f}; // difuso, mais claro para o piso
  GLfloat ks[] = {0.0f, 0.0f, 0.0f, 1.0f}; // sem componente especular (não brilha)
  GLfloat ns = 0.0f;                       // Sem brilho

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);  // componente ambiente
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);  // componente difuso
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks); // sem brilho especular
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ns); // brilho 0

  // Aqui você pode desenhar o piso com uma textura ou uma cor sólida
  glColor3f(0.6f, 0.6f, 0.6f); // Uma cor cinza, por exemplo

  // Desenhando o piso como um quadrado grande (pode ser um plano)
  glBegin(GL_QUADS);
  glVertex3f(-10.0f, -0.5f, -10.0f);
  glVertex3f(10.0f, -0.5f, -10.0f);
  glVertex3f(10.0f, -0.5f, 10.0f);
  glVertex3f(-10.0f, -0.5f, 10.0f);
  glEnd();

  glPopMatrix();
}
