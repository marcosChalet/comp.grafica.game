#include "collision-boxes.h"
#include <stdlib.h>

RelativeCollisionBox *create_relative_collision_box(float width, float height, float depth) {
  RelativeCollisionBox *relative_collision_box =
      (RelativeCollisionBox *)malloc(sizeof(RelativeCollisionBox));

  relative_collision_box->depth = depth;
  relative_collision_box->height = height;
  relative_collision_box->width = width;

  return relative_collision_box;
}

void destroy_relative_collision_box(RelativeCollisionBox *box) {
  free(box);
}

bool check_collision(AABB box1, AABB box2) {
  return (box1.x < box2.x + box2.width && box1.x + box1.width > box2.x &&
          box1.y < box2.y + box2.height && box1.y + box1.height > box2.y &&
          box1.z < box2.z + box2.depth && box1.z + box1.depth > box2.z);
}