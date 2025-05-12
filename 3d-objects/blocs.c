#include "blocs.h"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void draw_bloc(BlocBasic *b) {
  glPushMatrix();

  GLfloat mat_amb_diff[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_specular[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat mat_shininess[] = {0.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glColor3f(0.2, 0.9, 0.2);
  glTranslatef((b->x + b->size) / 2 - 0.5, (b->y + b->size) / 2 - 1.1, (b->z + b->size) / 2 - 1.1);
  glutSolidCube(b->size / 1.5);
  glPopMatrix();
}

void draw_moving_bloc(MovingBloc *mv) {
  glPushMatrix();

  GLfloat mat_amb_diff[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_specular[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat mat_shininess[] = {0.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glColor3f(0.2, 0.9, 0.2);
  glTranslatef((mv->x + mv->size) / 2 - 0.5, (mv->y + mv->size) / 2 - 1.1,
               (mv->z + mv->size) / 2 - 1.1);
  glutSolidCube(mv->size / 1.5);
  glPopMatrix();
}

BlocBasic *create_bloc(BlocBasic bloc) {
  BlocBasic *new_bloc = (BlocBasic *)malloc(sizeof(BlocBasic));

  new_bloc->x = bloc.x;
  new_bloc->y = bloc.y;
  new_bloc->z = bloc.z;
  new_bloc->size = bloc.size;
  new_bloc->bloc_type = bloc.bloc_type;
  new_bloc->behavior_type = bloc.behavior_type;
  new_bloc->update_behavior = bloc.update_behavior;

  return new_bloc;
}

void destroy_bloc_basic(BlocBasic *b) {
  free(b);
}

MovingBloc *create_moving_bloc(MovingBloc mv) {
  MovingBloc *new_bloc = (MovingBloc *)malloc(sizeof(MovingBloc));

  new_bloc->x = mv.x;
  new_bloc->y = mv.y;
  new_bloc->z = mv.z;
  new_bloc->size = mv.size;
  new_bloc->bloc_type = mv.bloc_type;
  new_bloc->behavior_type = mv.behavior_type;
  new_bloc->update_behavior = mv.update_behavior;
  new_bloc->amplitude = mv.amplitude;
  new_bloc->speed = mv.speed;

  return new_bloc;
}

void destroy_moving_bloc(MovingBloc *mb) {
  free(mb);
}

void print_bloc(BlocBasic *b) {
  if (!b) {
    printf("Bloco nulo.\n");
    return;
  }

  printf("Posição: (%.2f, %.2f, %.2f)\n", b->x, b->y, b->z);

  switch (b->bloc_type) {
  case BLOC_T_INVISIBLE:
    printf("Tipo de bloco: INVISÍVEL\n");
    break;
  case BLOC_T_GRASS:
    printf("Tipo de bloco: GRAMA\n");
    break;
  default:
    printf("Tipo de bloco: DESCONHECIDO\n");
  }

  switch (b->behavior_type) {
  case BLOC_T_SPAWN:
    printf("Comportamento: SPAWN\n");
    break;
  case BLOC_T_NONE:
    printf("Comportamento: NENHUM\n");
    break;
  case BLOC_T_MOVING:
    printf("Comportamento: MÓVEL\n");
    // Cast para MovingBloc
    {
      MovingBloc *mb = (MovingBloc *)b;
      printf("  Velocidade: %.2f\n", mb->speed);
      printf("  Amplitude: %.2f\n", mb->amplitude);
    }
    break;
  default:
    printf("Comportamento: DESCONHECIDO\n");
  }

  printf("\n");
}

void update_bloc_moving_behavior(void *bloc) {};
void update_bloc_rotating_behavior(void *bloc) {};