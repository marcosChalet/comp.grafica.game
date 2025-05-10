#include "steve.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawSteve(Steve *steve) {

  glPushMatrix(); // Salva o estado atual da transformação e do material

  glScalef(0.1f, 0.1f, 0.1f);
  glRotatef(180.0f, 0, 1, 0);
  glEnable(GL_NORMALIZE);

  // --- DEFINIÇÃO DO MATERIAL ---
  GLfloat ka[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat kd[] = {0.2f, 0.9f, 0.2f, 1.0f}; // cor principal (verde)
  GLfloat ks[] = {1.0f, 1.0f, 1.0f, 1.0f}; // brilho
  GLfloat ns = 20.0f;                      // intensidade do brilho

  // glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
  // glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
  // glMaterialf(GL_FRONT, GL_SHININESS, ns);

  // --- FIM DO MATERIAL ---

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, steve->mesh.vertices);

  if (steve->mesh.normals) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, steve->mesh.normals);
  }

  if (steve->mesh.texcoords) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, steve->mesh.texcoords);
  }

  glDrawArrays(GL_TRIANGLES, 0, steve->mesh.num_triangles * 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glPopMatrix(); // Restaura o estado anterior da transformação e do material
}

Steve *steveBuilder(char *path) {
  Steve *newSteve = malloc(sizeof(Steve));
  if (!newSteve) {
    perror("Steve builder memory allocation error");
    return NULL;
  }

  memset(&newSteve->mesh, 0, sizeof(Mesh));
  load_mesh(&newSteve->mesh, path);
  newSteve->draw = &drawSteve;

  return newSteve;
}