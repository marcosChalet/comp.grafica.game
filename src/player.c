#include "steve.h"
#include <GL/glut.h>
#include <math.h>

#define STEVE_PATH1 "./data/Steve1.obj"
#define STEVE_PATH2 "./data/Steve2.obj"

float jumpVelocity = -1.5f;
const float gravity = -0.009f;
const float jumpStrength = 0.15f;

float yaw = -90.0f, pitch = 0.0f;
float speed = 0.05f;
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;
float dirX, dirY, dirZ;
int keys[256] = {0};
int events[256] = {0};

Steve *steve1;
Steve *steve2;

void initCamera() {
  dirX = cosf(yaw * (M_PI / 180.0f));
  dirY = 0.0f;
  dirZ = sinf(yaw * (M_PI / 180.0f));
}

void updateCamera() {
  float lookX = camX + dirX;
  float lookY = camY + dirY;
  float lookZ = camZ + dirZ;

  gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0f, 1.0f, 0.0f);
}

void updatePosition() {
  float moveX = 0, moveZ = 0;

  if (keys['w']) {
    moveX += dirX;
    moveZ += dirZ;
  }
  if (keys['s']) {
    moveX -= dirX;
    moveZ -= dirZ;
  }
  if (keys['a']) {
    moveX += dirZ;
    moveZ -= dirX;
  }
  if (keys['d']) {
    moveX -= dirZ;
    moveZ += dirX;
  }

  camX += moveX * speed;
  camZ += moveZ * speed;

  camY += jumpVelocity;
  jumpVelocity += gravity;

  if (camY <= 0.0f) {
    camY = 0.0f;
    jumpVelocity = 0.0f;
  }
}
#include <stdio.h>
void processKeyboard(unsigned char key, int isPressed) {
  keys[key] = isPressed;

  // Inicia o pulo ao pressionar espaço (e apenas se estiver no chão)
  if (key == ' ' && isPressed && camY <= 0.0f) {
    jumpVelocity = jumpStrength;
  }
}

void processMouse(float offsetX, float offsetY) {
  // deixa a câmera mais suave
  if (offsetX > 6 || offsetX < -6) {
    offsetX *= 0.3;
  }

  yaw += offsetX / 5;
  pitch += offsetY / 10;

  if (pitch > 80.0f)
    pitch = 80.0f;
  if (pitch < -15.0f)
    pitch = -15.0f;

  float radYaw = yaw * (M_PI / 180.0f);
  float radPitch = pitch * (M_PI / 180.0f);

  dirX = cosf(radYaw) * cosf(radPitch);
  dirY = sinf(radPitch);
  dirZ = sinf(radYaw) * cosf(radPitch);
}

void drawPlayer() {

  /** teste para andar infinitamente */
  static int walk;
  static int tick = 0;
  tick++;
  if (tick % 15 == 0) {
    walk = !walk;
  }

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity(); // tirar isso e mover o Steve com 'w'
  glTranslatef(0.0f, -0.3f, -0.3f);

  if (keys['s']) {
    glRotatef(180.0, 0, 1, 0);
    glTranslatef(0.0f, 0.0f, 0.5f);
  }
  if (keys['d']) {
    glRotatef(90.0, 0, 1, 0);
    glTranslatef(0.27f, 0.0f, 0.27f);
  }
  if (keys['a']) {
    glRotatef(-90.0, 0, 1, 0);
    glTranslatef(-0.27f, 0.0f, 0.27f);
  }

  if (walk) {
    steve1->draw(steve1);
  } else {
    steve2->draw(steve2);
  }
  glPopMatrix();
}

void loadPlayer() {
  steve1 = steveBuilder(STEVE_PATH1);
  steve2 = steveBuilder(STEVE_PATH2);
}