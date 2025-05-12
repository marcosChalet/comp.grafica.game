#ifndef MESH_LOADER_H
#define MESH_LOADER_H

typedef struct {
  float *vertices;
  float *normals;
  float *texcoords;
  int num_triangles;
} Mesh;

void load_mesh(Mesh *mesh, const char *filename);
void draw_mesh(Mesh *mesh);
void free_mesh(Mesh *mesh);

#endif