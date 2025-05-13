#ifndef COLLISION_BOXES_H
#define COLLISION_BOXES_H

typedef struct relative_collision_box {
  float width;
  float height;
  float depth;
} RelativeCollisionBox;

typedef struct {
  float x, y, z;
  float width, height, depth;
} AABB;

RelativeCollisionBox *create_relative_collision_box(float width, float height, float depth);
void destroy_relative_collision_box(RelativeCollisionBox *box);

bool check_collision(AABB box1, AABB box2);

#endif