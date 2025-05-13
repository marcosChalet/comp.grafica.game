#include "import-object.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void draw_imported_object(ImportedObject *object, float x, float y, float z, float scale_size) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(scale_size, scale_size, scale_size);

  // glEnable(GL_NORMALIZE);
  GLfloat ka[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat kd[] = {0.5f, 0.5f, 0.9f, 1.0f};
  GLfloat ks[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat ns = 64.0f;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
  glMaterialf(GL_FRONT, GL_SHININESS, ns);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, object->mesh.vertices);

  if (object->mesh.normals) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, object->mesh.normals);
  }

  if (object->mesh.texcoords) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, object->mesh.texcoords);
  }

  glDrawArrays(GL_TRIANGLES, 0, object->mesh.num_triangles * 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glPopMatrix();
}

ImportedObject *import_object(char *path) {
  ImportedObject *new_object = malloc(sizeof(ImportedObject));
  if (!new_object) {
    perror("Sword memory allocation error");
    return NULL;
  }

  memset(&new_object->mesh, 0, sizeof(Mesh));
  load_mesh(&new_object->mesh, path);

  return new_object;
}