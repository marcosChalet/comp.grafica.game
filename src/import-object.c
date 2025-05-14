#include "import-object.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void infinit_rotate_imported_object() {
  static int degree_rotate_delta = 0;
  if (degree_rotate_delta >= 360) {
    degree_rotate_delta = 0;
  }
  glRotatef(degree_rotate_delta++, 1, 1, 1);
}

void draw_imported_object(ImportedObject *object, float x, float y, float z, float scale_size) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(scale_size, scale_size, scale_size);

  glEnable(GL_NORMALIZE);
  GLfloat ka[] = {0.5f, 0.5f, 0.9f, 1.0f};
  GLfloat kd[] = {0.0f, 0.0f, 0.9f, 1.0f};
  GLfloat ks[] = {0.2f, 0.3f, 0.95f, 1.0f};
  GLfloat ns = 50.0f;

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

  infinit_rotate_imported_object();
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