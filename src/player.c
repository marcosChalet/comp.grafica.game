#include <GL/glut.h>
#include <math.h>

int isJumping = 0;
float jumpVelocity = 0.0f;
const float gravity = -0.01f;
const float jumpStrength = 0.2f;

float yaw = -90.0f, pitch = 0.0f;
float speed = 0.1f;
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;
float dirX, dirY, dirZ;
int keys[256] = {0};
int events[256] = {0};

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

  if (isJumping) {
    camY += jumpVelocity;
    jumpVelocity += gravity;

    if (camY <= 0.0f) {
      camY = 0.0f;
      isJumping = 0;
      jumpVelocity = 0.0f;
    }
  }
}

void processKeyboard(unsigned char key, int isPressed) {
  keys[key] = isPressed;

  // Inicia o pulo ao pressionar espaço (e apenas se estiver no chão)
  if (key == ' ' && isPressed && !isJumping && camY <= 0.0f) {
    isJumping = 1;
    jumpVelocity = jumpStrength;
  }
}

void processMouse(float offsetX, float offsetY) {
  yaw += offsetX;
  pitch += offsetY;

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
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0.0f, -0.5f, -1.0f);
  glColor3f(1.0f, 1.0f, 0.0f);
  glutSolidCube(0.2);
  glPopMatrix();
}
