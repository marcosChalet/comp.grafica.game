#include "parse-blocks.h"
#include "player.h"
#include "scene.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int lastMouseX, lastMouseY;
int firstMouse = 1;
int ignoreWarp = 0;

void init() {
  glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
  initCamera();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // atualizar blocos
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
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
  processKeyboard(key, 1);
}

void keyboardUp(unsigned char key, int x, int y) {
  processKeyboard(key, 0);
}

void passiveMotion(int x, int y) {
  int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
  int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
  int centerX = windowWidth / 2;
  int centerY = windowHeight / 2;

  if (ignoreWarp) {
    ignoreWarp = 0;
    return;
  }

  if (firstMouse) {
    lastMouseX = centerX;
    lastMouseY = centerY;
    firstMouse = 0;
    ignoreWarp = 1;
    glutWarpPointer(centerX, centerY);
    return;
  }

  int deltaX = x - centerX;
  int deltaY = centerY - y;

  float sensitivity = 0.08f;
  processMouse(deltaX * sensitivity, deltaY * sensitivity);

  ignoreWarp = 1;
  glutWarpPointer(centerX, centerY);
}

void timer(int value) {
  updatePosition();
  glutPostRedisplay();
  glutTimerFunc(16, timer, 0);
}

int main(int argc, char **argv) {
  // glutInit(&argc, argv);
  // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  // glutInitWindowSize(1920, 1080); // ou qualquer resolução do seu monitor
  // glutCreateWindow("Jogo em 3D - Primeira Pessoa");
  // glutFullScreen();

  // glEnable(GL_DEPTH_TEST);

  // int w = glutGet(GLUT_WINDOW_WIDTH);
  // int h = glutGet(GLUT_WINDOW_HEIGHT);
  // glViewport(0, 0, w, h);
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // gluPerspective(60.0, (float)w / (float)h, 0.1, 100.0);
  // glMatrixMode(GL_MODELVIEW);

  // glutDisplayFunc(display);

  // glutKeyboardFunc(keyboard);
  // glutKeyboardUpFunc(keyboardUp);
  // glutPassiveMotionFunc(passiveMotion);
  // glutMotionFunc(passiveMotion);

  // glutTimerFunc(0, timer, 0);

  // glutSetCursor(GLUT_CURSOR_NONE);
  // init();
  // glutMainLoop();

  load_blocks_from_file("./3d-objects/blocks.conf");

  return 0;
}
