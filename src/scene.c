#include "scene.h"
#include "floor.h"
#include "grassBlock.h"
#include "grassPlatform.h"
#include "player.h"
#include <GL/glut.h>

void drawScene(GrassBlock *grassBlock, Sword *sword) {
  updateCamera();

  /**
   * [Ideia do que fazer]
   * Ir implementando o mapa corretamente. Criar templates dos
   * elementos que irão aparecer no mapa, adicionar textura (no final),
   * e chamar aqui fazendo uma translação para sua posição correta no
   * mapa.
   **/

  // bloco 0
  glPushMatrix();
  glTranslatef(12.0f, -0.7f, 5.0f);
  grassBlock->draw(grassBlock);
  glPopMatrix();

  // bloco 1
  glPushMatrix();
  glTranslatef(10.0f, 0.0f, 5.0f);
  grassBlock->draw(grassBlock);
  glPopMatrix();

  // bloco 2
  glPushMatrix();
  glTranslatef(8.0f, 1.0f, 5.0f);
  grassBlock->draw(grassBlock);
  glPopMatrix();

  // bloco 3
  glPushMatrix();
  glTranslatef(6.0f, 2.0f, 5.0f);
  grassBlock->draw(grassBlock);
  glPopMatrix();

  // plataforma
  glPushMatrix();
  glTranslatef(3.0f, 3.0f, 5.0f);
  drawGrassPlatform();
  glPopMatrix();

  // bloco 4
  glPushMatrix();
  glTranslatef(3.0f, 3.0f, 9.0f);
  grassBlock->draw(grassBlock);
  glPopMatrix();

  // bloco 5
  glPushMatrix();
  glTranslatef(3.0f, 1.5f, 12.0f);
  grassBlock->draw(grassBlock);
  glPopMatrix();

  // prêmio (espada)
  glPushMatrix();
  glTranslatef(-3.8f, 2.4f, 7.2f);
  sword->draw(sword);
  glPopMatrix();

  // chão com material
  drawFloor(0.0f, 0.0f, 0.0f, 2.0f, 2.0f, 2.0f);

  drawPlayer();
}
