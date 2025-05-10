#include "meshLoader.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void load_mesh(Mesh *mesh, const char *filename) {
//   FILE *file = fopen(filename, "r");
//   if (!file) {
//     printf("Erro ao abrir %s\n", filename);
//     return;
//   }

//   float *temp_vertices = NULL;
//   float *temp_normals = NULL;
//   float *temp_texcoords = NULL;
//   int num_verts = 0, num_norms = 0, num_texs = 0;

//   char line[256];
//   while (fgets(line, sizeof(line), file)) {
//     if (line[0] == 'v') {
//       float x, y, z;
//       if (line[1] == ' ') {
//         sscanf(line + 2, "%f %f %f", &x, &y, &z);
//         temp_vertices = realloc(temp_vertices, (num_verts + 3) * sizeof(float));
//         temp_vertices[num_verts++] = x;
//         temp_vertices[num_verts++] = y;
//         temp_vertices[num_verts++] = z;
//       } else if (line[1] == 't') {
//         sscanf(line + 3, "%f %f", &x, &y);
//         temp_texcoords = realloc(temp_texcoords, (num_texs + 2) * sizeof(float));
//         temp_texcoords[num_texs++] = x;
//         temp_texcoords[num_texs++] = y;
//       } else if (line[1] == 'n') {
//         sscanf(line + 3, "%f %f %f", &x, &y, &z);
//         temp_normals = realloc(temp_normals, (num_norms + 3) * sizeof(float));
//         temp_normals[num_norms++] = x;
//         temp_normals[num_norms++] = y;
//         temp_normals[num_norms++] = z;
//       }
//     } else if (line[0] == 'f') {
//       // Armazena temporariamente até 10 vértices por face
//       int v[10], t[10], n[10];
//       int matches[10];
//       int count = 0;

//       char *token = strtok(line + 2, " \n");
//       while (token && count < 10) {
//         matches[count] = sscanf(token, "%d/%d/%d", &v[count], &t[count], &n[count]);
//         v[count]--;
//         t[count]--;
//         n[count]--;
//         count++;
//         token = strtok(NULL, " \n");
//       }

//       if (count < 3)
//         continue; // Inválido

//       // Se tiver 4 vértices, divide em 2 triângulos: 0-1-2 e 0-2-3
//       int triangulation[][3] = {{0, 1, 2}, {0, 2, 3}};

//       int num_tris = (count == 4) ? 2 : (count == 3) ? 1 : 0;
//       for (int t_idx = 0; t_idx < num_tris; t_idx++) {
//         for (int i = 0; i < 3; i++) {
//           int idx = (count == 4) ? triangulation[t_idx][i] : i;

//           mesh->vertices = realloc(mesh->vertices, (mesh->num_triangles * 9 + 9) *
//           sizeof(float)); memcpy(&mesh->vertices[mesh->num_triangles * 9 + i * 3],
//           &temp_vertices[v[idx] * 3],
//                  3 * sizeof(float));

//           if (temp_texcoords && matches[idx] > 1) {
//             mesh->texcoords =
//                 realloc(mesh->texcoords, (mesh->num_triangles * 6 + 6) * sizeof(float));
//             memcpy(&mesh->texcoords[mesh->num_triangles * 6 + i * 2], &temp_texcoords[t[idx] *
//             2],
//                    2 * sizeof(float));
//           }

//           if (temp_normals && matches[idx] > 2) {
//             mesh->normals = realloc(mesh->normals, (mesh->num_triangles * 9 + 9) *
//             sizeof(float)); memcpy(&mesh->normals[mesh->num_triangles * 9 + i * 3],
//             &temp_normals[n[idx] * 3],
//                    3 * sizeof(float));
//           }
//         }
//         mesh->num_triangles++;
//       }
//     }
//   }

//   fclose(file);
//   free(temp_vertices);
//   free(temp_normals);
//   free(temp_texcoords);
// }
void load_mesh(Mesh *mesh, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Erro ao abrir %s\n", filename);
    return;
  }

  float *temp_vertices = NULL;
  float *temp_normals = NULL;
  float *temp_texcoords = NULL;
  int num_verts = 0, num_norms = 0, num_texs = 0;

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'v') {
      float x, y, z;
      if (line[1] == ' ') {
        sscanf(line + 2, "%f %f %f", &x, &y, &z);
        temp_vertices = realloc(temp_vertices, (num_verts + 3) * sizeof(float));
        temp_vertices[num_verts++] = x;
        temp_vertices[num_verts++] = y;
        temp_vertices[num_verts++] = z;
      } else if (line[1] == 't') {
        sscanf(line + 3, "%f %f", &x, &y);
        temp_texcoords = realloc(temp_texcoords, (num_texs + 2) * sizeof(float));
        temp_texcoords[num_texs++] = x;
        temp_texcoords[num_texs++] = y;
      } else if (line[1] == 'n') {
        sscanf(line + 3, "%f %f %f", &x, &y, &z);
        temp_normals = realloc(temp_normals, (num_norms + 3) * sizeof(float));
        temp_normals[num_norms++] = x;
        temp_normals[num_norms++] = y;
        temp_normals[num_norms++] = z;
      }
    } else if (line[0] == 'f') {
      // Armazena temporariamente até 10 vértices por face
      int v[10], t[10], n[10];
      int matches[10];
      int count = 0;

      char *token = strtok(line + 2, " \n");
      while (token && count < 10) {
        matches[count] = sscanf(token, "%d/%d/%d", &v[count], &t[count], &n[count]);
        v[count]--;
        t[count]--;
        n[count]--;
        count++;
        token = strtok(NULL, " \n");
      }

      if (count < 3)
        continue; // Inválido

      // Se tiver 4 vértices, divide em 2 triângulos: 0-1-2 e 0-2-3
      int triangulation[][3] = {{0, 1, 2}, {0, 2, 3}};

      int num_tris = (count == 4) ? 2 : (count == 3) ? 1 : 0;
      for (int t_idx = 0; t_idx < num_tris; t_idx++) {
        for (int i = 0; i < 3; i++) {
          int idx = (count == 4) ? triangulation[t_idx][i] : i;

          mesh->vertices = realloc(mesh->vertices, (mesh->num_triangles * 9 + 9) * sizeof(float));
          memcpy(&mesh->vertices[mesh->num_triangles * 9 + i * 3], &temp_vertices[v[idx] * 3],
                 3 * sizeof(float));

          if (temp_texcoords && matches[idx] > 1) {
            mesh->texcoords =
                realloc(mesh->texcoords, (mesh->num_triangles * 6 + 6) * sizeof(float));
            memcpy(&mesh->texcoords[mesh->num_triangles * 6 + i * 2], &temp_texcoords[t[idx] * 2],
                   2 * sizeof(float));
          }

          if (temp_normals && matches[idx] > 2) {
            mesh->normals = realloc(mesh->normals, (mesh->num_triangles * 9 + 9) * sizeof(float));
            memcpy(&mesh->normals[mesh->num_triangles * 9 + i * 3], &temp_normals[n[idx] * 3],
                   3 * sizeof(float));
          }
        }
        mesh->num_triangles++;
      }
    }
  }

  fclose(file);
  free(temp_vertices);
  free(temp_normals);
  free(temp_texcoords);
}

void draw_mesh(Mesh *mesh) {
  glScalef(0.5f, 0.5f, 0.5f);
  glTranslatef(-10, -2, -3);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);

  if (mesh->normals) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, mesh->normals);
  }

  if (mesh->texcoords) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, mesh->texcoords);
  }

  glDrawArrays(GL_TRIANGLES, 0, mesh->num_triangles * 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void free_mesh(Mesh *mesh) {
  free(mesh->vertices);
  free(mesh->normals);
  free(mesh->texcoords);
  mesh->num_triangles = 0;
}