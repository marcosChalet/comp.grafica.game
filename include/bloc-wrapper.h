#ifndef BLOC_WRAPPER_H
#define BLOC_WRAPPER_H

#include "blocs.h"

typedef struct bloc_wrapper {
  int id;
  void *bloc;
  struct bloc_wrapper *next;
  struct bloc_wrapper *prev;
} BlocWrapper;

BlocWrapper *create_bloc_wrapper(int id, void *bloc);
void destroy_bloc_wrapper(BlocWrapper *wrapper);

#endif