#ifndef PLAYER_H
#define PLAYER_H

typedef struct player {
  float x, y, z;
  int isJumping;
  float jumpVelocity;
  float jumpStrength;
  float speed;
} Player;

void drawPlayer();
void updatePosition();
void processKeyboard(unsigned char key, int isPressed);
void processMouse(float offsetX, float offsetY);
void initCamera();
void updateCamera();

#endif