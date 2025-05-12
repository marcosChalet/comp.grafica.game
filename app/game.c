#include "blocks.h"
#include "global.h"
#include "parse-blocks.h"
#include "player.h"
#include "scene.h"
#include "stage-loader.h"

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

Player player;

void init() {
  glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
  init_player(0, 0, 0, &player);
  load_stage("./3d-objects/stage-1.conf");
  // load_blocks_from_file("./3d-objects/blocks.conf", blocks);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // atualizar blockos
  //  as peculiaridades de cada um e registra ações no player na fila de evento
  // atuliazar fisica
  //  registra em uma fila de eventos
  //    gravidade
  //    colisão
  //    talvez deslizar
  // atualizar player
  //   processa eventos de input
  //    mouse e teclado e registra na fila

  glLoadIdentity();
  drawScene();
  render_stage();
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
  change_position_direction(key, 1);
}

void keyboardUp(unsigned char key, int x, int y) {
  change_position_direction(key, 0);
}

void passiveMotion(int x, int y) {
  int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
  int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
  float center_x = windowWidth / 2;
  float center_y = windowHeight / 2;
  static int ignore_warp = 0;

  if (ignore_warp) {
    ignore_warp = 0;
    return;
  }

  float delta_x = x - center_x;
  float delta_y = center_y - y;
  change_look_direction(delta_x, delta_y);

  ignore_warp = 1;
  glutWarpPointer(center_x, center_y);
}

void timer(int value) {
  move_player();
  glutPostRedisplay();
  glutTimerFunc(16, timer, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowSize(1920, 1080); // ou qualquer resolução do seu monitor
  glutCreateWindow("Jogo em 3D - Primeira Pessoa");
  glutFullScreen();

  glEnable(GL_DEPTH_TEST);

  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (float)w / (float)h, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);

  glutDisplayFunc(display);

  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutPassiveMotionFunc(passiveMotion);
  glutMotionFunc(passiveMotion);

  glutTimerFunc(0, timer, 0);

  glutSetCursor(GLUT_CURSOR_NONE);
  init();
  glutMainLoop();

  return 0;
}
