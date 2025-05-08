#include "platform.h"
#include "player.h"
#include <GL/glut.h>

void drawScene() {
  updateCamera();

  /**
   * [Ideia do que fazer]
   * Ir implementando o mapa corretamente. Criar templates dos
   * elementos que irão aparecer no mapa, adicionar textura (no final),
   * e chamar aqui fazendo uma translação para sua posição correta no
   * mapa.
   **/

  // exemplo
  drawPlatform(6.0f, 0.0f, 0.0f, 4.0f, 0.2f, 3.0f);

  /**
   * mudar o cenário depois
   */

  // chão
  glColor3f(0.5f, 0.5f, 0.5f);
  glBegin(GL_QUADS);
  glVertex3f(-20.0f, -1.5f, 20.0f);
  glVertex3f(20.0f, -1.5f, 20.0f);
  glVertex3f(20.0f, -1.5f, -20.0f);
  glVertex3f(-20.0f, -1.5f, -20.0f);
  glEnd();

  // bloco 1
  glPushMatrix();
  glTranslatef(0.0f, -1.5f + (2.0f / 2.0f), -5.0f); // y = -0.5
  glScalef(2.0f, 2.0f, 2.0f);
  glColor3f(0.8f, 0.2f, 0.2f);
  glutSolidCube(1.0);
  glPopMatrix();

  // bloco 2
  glPushMatrix();
  glTranslatef(3.0f, -1.5f + (2.5f / 2.0f), -8.0f); // y = -0.25
  glScalef(2.5f, 2.5f, 2.5f);
  glColor3f(0.2f, 0.2f, 0.8f);
  glutSolidCube(1.0);
  glPopMatrix();

  // bloco 3
  glPushMatrix();
  glTranslatef(-4.0f, -1.5f + (1.0f / 2.0f), -12.0f); // y = -1.0
  glScalef(3.0f, 1.0f, 3.0f);
  glColor3f(0.2f, 0.8f, 0.2f);
  glutSolidCube(1.0);
  glPopMatrix();

  drawPlayer();
}
