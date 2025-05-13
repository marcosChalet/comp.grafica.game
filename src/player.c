#include "player.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

Player *player_ptr;

// float yaw = -90.0f, pitch = 0.0f;

const float gravity = -0.0009f;
bool is_jumping = false;

int keys[256] = {0};

Player *create_player() {
  Player *player_ptr = (Player *)malloc(sizeof(Player));

  player_ptr->x = 0;
  player_ptr->y = 0;
  player_ptr->z = 0;

  player_ptr->yaw = -90.0f;
  player_ptr->pitch = 0.0f;

  player_ptr->speed = 0.015f;
  player_ptr->isJumping = 0;
  player_ptr->jumpStrength = 0.022f;
  player_ptr->jumpVelocity = 0.0f;
  player_ptr->sensibility = 0.03f;
  player_ptr->groundLevel = player_ptr->y;

  player_ptr->gazeDirectionX = cosf(player_ptr->yaw * (M_PI / 180.0f));
  player_ptr->gazeDirectionY = 0.0f;
  player_ptr->gazeDirectionZ = sinf(player_ptr->yaw * (M_PI / 180.0f));

  return player_ptr;
}

void init_player(float x, float y, float z, Player *player_ref) {
  player_ptr = player_ref;

  player_ptr->x = x;
  player_ptr->y = y;
  player_ptr->z = z;
}

void update_player_sensibility(float sensibility) {
  player_ptr->sensibility = sensibility;
}

void update_player_position() {
  GLdouble centerX = player_ptr->x + player_ptr->gazeDirectionX;
  GLdouble centerY = player_ptr->y + player_ptr->gazeDirectionY;
  GLdouble centerZ = player_ptr->z + player_ptr->gazeDirectionZ;

  gluLookAt(player_ptr->x, player_ptr->y, player_ptr->z, centerX, centerY, centerZ, 0.0f, 1.0f,
            0.0f);
}

void move_player() {
  float moveX = 0, moveZ = 0;

  if (keys['w']) {
    moveX += player_ptr->gazeDirectionX;
    moveZ += player_ptr->gazeDirectionZ;
  }
  if (keys['s']) {
    moveX -= player_ptr->gazeDirectionX;
    moveZ -= player_ptr->gazeDirectionZ;
  }
  if (keys['a']) {
    moveX += player_ptr->gazeDirectionZ;
    moveZ -= player_ptr->gazeDirectionX;
  }
  if (keys['d']) {
    moveX -= player_ptr->gazeDirectionZ;
    moveZ += player_ptr->gazeDirectionX;
  }

  if (keys[' '] && !player_ptr->isJumping) {
    player_ptr->jumpVelocity = player_ptr->jumpStrength;
    player_ptr->isJumping = true;
  }

  player_ptr->x += moveX * player_ptr->speed;
  player_ptr->z += moveZ * player_ptr->speed;

  if (player_ptr->isJumping) {
    player_ptr->y += player_ptr->jumpVelocity;
    player_ptr->jumpVelocity += gravity;

    if (player_ptr->y <= player_ptr->groundLevel) {
      player_ptr->y = player_ptr->groundLevel;
      player_ptr->isJumping = false;
      player_ptr->jumpVelocity = 0.0f;
    }
  }
}

void change_position_direction(unsigned char key, int isPressed) {
  keys[key] = isPressed;
}

void change_look_direction(float offsetX, float offsetY) {
  player_ptr->yaw += offsetX * player_ptr->sensibility;
  player_ptr->pitch += offsetY * player_ptr->sensibility;

  if (player_ptr->pitch > 80.0f)
    player_ptr->pitch = 80.0f;
  if (player_ptr->pitch < -25.0f)
    player_ptr->pitch = -25.0f;

  float radYaw = player_ptr->yaw * (M_PI / 180.0f);
  float radPitch = player_ptr->pitch * (M_PI / 180.0f);

  player_ptr->gazeDirectionX = cosf(radYaw) * cosf(radPitch);
  player_ptr->gazeDirectionY = sinf(radPitch);
  player_ptr->gazeDirectionZ = sinf(radYaw) * cosf(radPitch);
}