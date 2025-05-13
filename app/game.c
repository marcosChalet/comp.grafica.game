#include "blocks.h"
#include "global.h"
#include "parse-blocks.h"
#include "player.h"
#include "scene.h"
#include "stage-loader.h"
#include "sun.h"

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

Player *player;

void init() {
  glClearColor(0.529f, 0.808f, 0.922f, 1.0);
  printf("initializing global stage\n");
  init_global_data();
  player = get_global_player();
  printf("loading stage\n");
  load_stage("./3d-objects/stage-1.conf");
  sun_light_init();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  drawScene();
  render_stage();
  render_sun();

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

  glutInitWindowSize(1920, 1080);
  glutCreateWindow("Minecraft - Parkour");
  glutFullScreen();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (float)w / (float)h, 0.1, 20000.0);
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
