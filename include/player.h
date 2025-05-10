#ifndef PLAYER_H
#define PLAYER_H

void loadPlayer();
void drawPlayer();

void updatePosition();
void processKeyboard(unsigned char key, int isPressed);
void processMouse(float offsetX, float offsetY);
void initCamera();
void updateCamera();

#endif