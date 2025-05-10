#ifndef MESH_LOADER_H
#define MESH_LOADER_H

typedef struct {
  float *vertices;   // Vértices intercalados (x,y,z)
  float *normals;    // Normais intercaladas (x,y,z)
  float *texcoords;  // Coordenadas de textura (u,v)
  int num_triangles; // Número de triângulos
} Mesh;

void load_mesh(Mesh *mesh, const char *filename);
void draw_mesh(Mesh *mesh);
void free_mesh(Mesh *mesh);

#endif