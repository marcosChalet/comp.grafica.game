#include "global.h"
#include "platform.h"
#include "player.h"
#include "routines.h"
#include <GL/glut.h>
#include <stdio.h>

void drawScene() {
  Player *player = get_global_player();

  // scene sample
  update_player_position();

  // BlockBasic *block = check_collisions();
  // if (block) {
  //   CollisionDirection collision_direction = check_player_block_collision_direction(player,
  //   block); printf("coll: %d\n", collision_direction);

  //   // if (collision_direction == COLLISION_LEFT || collision_direction == COLLISION_RIGHT) {
  //   //   player->x -= player->gazeDirectionX * player->speed; // desfaz o movimento em X
  //   // }
  //   // if (collision_direction == COLLISION_FRONT || collision_direction == COLLISION_BACK) {
  //   //   player->z -= player->gazeDirectionZ * player->speed; // desfaz o movimento em Z
  //   // }
  //   if (collision_direction == COLLISION_TOP || collision_direction == COLLISION_BOTTOM) {
  //     player->jumpVelocity = 0.0f;
  //     player->isJumping = 0;
  //     player->y = block->y + block->relative_collision_box->height; // ajusta para cima
  //   }
  // } else {
  //   player->isJumping = 1;
  // }

  // drawPlatform(6.0f, 0.0f, 0.0f, 4.0f, 0.2f, 3.0f);

  // chão
  // glColor3f(0.5f, 0.5f, 0.5f);
  // glBegin(GL_QUADS);
  // glVertex3f(-3.0f, -0.1f, 3.0f);
  // glVertex3f(3.0f, -0.1f, 3.0f);
  // glVertex3f(3.0f, -0.1f, -3.0f);
  // glVertex3f(-3.0f, -0.1f, -3.0f);
  // glEnd();

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
