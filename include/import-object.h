#ifndef IMPORT_OBJECT_H
#define IMPORT_OBJECT_H

#include "mesh-loader.h"

typedef struct imported_object {
  Mesh mesh;
} ImportedObject;

ImportedObject *import_object(char *path);
void draw_imported_object(ImportedObject *object, float x, float y, float z, float scale_size);

#endif