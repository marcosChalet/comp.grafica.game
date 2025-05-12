#ifndef BLOCS_H
#define BLOCS_H

#include <stdbool.h>

typedef enum bloc_behavior_type {
  BLOC_T_SPAWN,
  BLOC_T_NONE,
  BLOC_T_MOVING,
} BlocBehaviorType;

typedef enum bloc_type {
  BLOC_T_INVISIBLE,
  BLOC_T_GRASS,
} BlocTypeEnum;

#define BLOC_BASE                                                                                  \
  float x, y, z;                                                                                   \
  float size;                                                                                      \
  void (*update_behavior)(void *);                                                                 \
  BlocBehaviorType behavior_type;                                                                  \
  BlocTypeEnum bloc_type;

typedef struct generic_bloc {
  void *bloc;
  BlocBehaviorType type;
} BlocGeneric;

typedef struct bloc {
  BLOC_BASE
} BlocBasic;

typedef struct moving_bloc {
  BLOC_BASE
  float start_position_z;
  bool is_backing;
  float speed;
  float amplitude;
} MovingBloc;

BlocBasic *create_bloc(BlocBasic);
void destroy_bloc_basic(BlocBasic *);

MovingBloc *create_moving_bloc(MovingBloc);
void destroy_moving_bloc(MovingBloc *);

void print_bloc(BlocBasic *b);

void draw_bloc(BlocBasic *b);
void draw_moving_bloc(MovingBloc *mv);

// Behavior functions
void update_bloc_moving_behavior(void *);
void update_bloc_rotating_behavior(void *);

#endif