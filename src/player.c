#include "player.h"
#include "global.h"
#include "routines.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

Player *player_ptr;

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
  player_ptr->groundLevel = -1000;

  player_ptr->gazeDirectionX = cosf(player_ptr->yaw * (M_PI / 180.0f));
  player_ptr->gazeDirectionY = 0.0f;
  player_ptr->gazeDirectionZ = sinf(player_ptr->yaw * (M_PI / 180.0f));

  player_ptr->relative_collision_box = create_relative_collision_box(0.09, 0.18, 0.09);
  player_ptr->collisionYOffset = -0.18;

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
  GlobalData *g = get_global_obj();
  Player *p = player_ptr;

  float moveX = 0, moveZ = 0;

  if (keys['r']) {
    SpawnPoint *spawn_point = get_spawn_point();
    p->x = spawn_point->x;
    p->y = spawn_point->y;
    p->z = spawn_point->z;

    return;
  }

  // Direção de movimento com base nas teclas
  if (keys['w']) {
    moveX += p->gazeDirectionX;
    moveZ += p->gazeDirectionZ;
  }
  if (keys['s']) {
    moveX -= p->gazeDirectionX;
    moveZ -= p->gazeDirectionZ;
  }
  if (keys['a']) {
    moveX += p->gazeDirectionZ;
    moveZ -= p->gazeDirectionX;
  }
  if (keys['d']) {
    moveX -= p->gazeDirectionZ;
    moveZ += p->gazeDirectionX;
  }

  // Normaliza vetor para evitar correr mais rápido na diagonal
  float length = sqrtf(moveX * moveX + moveZ * moveZ);
  if (length > 0) {
    moveX /= length;
    moveZ /= length;
  }

  // ---- Movimento em X com correção ----
  p->x += moveX * p->speed;
  void *collided = check_collisions();
  if (collided != NULL) {
    p->x -= moveX * p->speed; // desfaz o movimento se colidiu
  }

  // ---- Movimento em Z com correção ----
  p->z += moveZ * p->speed;
  collided = check_collisions();
  if (collided != NULL) {
    p->z -= moveZ * p->speed; // desfaz o movimento se colidiu
  }

  // ---- Pulo e gravidade (Y) ----
  if (keys[' '] && !p->isJumping) {
    p->jumpVelocity = p->jumpStrength;
    p->isJumping = true;
  }

  p->y += p->jumpVelocity;
  p->jumpVelocity += gravity;

  collided = check_collisions();
  if (collided != NULL) {
    // Verifica direção da colisão
    CollisionDirection dir = check_player_block_collision_direction(p, (BlockBasic *)collided);
    if (dir == COLLISION_BOTTOM) {
      // Tocou o chão
      p->isJumping = false;
      p->jumpVelocity = 0.0f;
      // Alinha com o topo do bloco
      BlockBasic *b = (BlockBasic *)collided;
      p->y = b->y + b->relative_collision_box->height - p->collisionYOffset;
    } else {
      // Colidiu no teto
      p->y -= p->jumpVelocity; // desfaz se bateu no teto
      p->jumpVelocity = 0.0f;
    }
  }
}

void is_player_colliding() {}

void change_position_direction(unsigned char key, int isPressed) {
  keys[key] = isPressed;
}

void change_look_direction(float offsetX, float offsetY) {
  player_ptr->yaw += offsetX * player_ptr->sensibility;
  player_ptr->pitch += offsetY * player_ptr->sensibility;

  if (player_ptr->pitch > 80.0f)
    player_ptr->pitch = 80.0f;
  if (player_ptr->pitch < -89.0f)
    player_ptr->pitch = -89.0f;

  float radYaw = player_ptr->yaw * (M_PI / 180.0f);
  float radPitch = player_ptr->pitch * (M_PI / 180.0f);

  player_ptr->gazeDirectionX = cosf(radYaw) * cosf(radPitch);
  player_ptr->gazeDirectionY = sinf(radPitch);
  player_ptr->gazeDirectionZ = sinf(radYaw) * cosf(radPitch);
}