#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>

typedef struct player {
  GLdouble x;
  GLdouble y;
  GLdouble z;
  GLdouble gazeDirectionX;
  GLdouble gazeDirectionY;
  GLdouble gazeDirectionZ;
  GLdouble groundLevel;
  float sensibility;
  float jumpVelocity;
  float jumpStrength;
  int isJumping;
  float speed;
} Player;

void move_player();
void change_position_direction(unsigned char key, int isPressed);
void init_player(float x, float y, float z, Player *player_ref);
void change_look_direction(float offsetX, float offsetY);
void update_player_sensibility(float sensibility);
void update_player_position();

#endif