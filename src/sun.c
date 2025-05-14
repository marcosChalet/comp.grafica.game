#include "global.h"

#include <GL/glut.h>

float sun_x;
float sun_z;
float sun_y;

#define PARALLAX_FACTOR 0.2f
#define SUN_INITIAL_POSITION_X -9000.0f
#define SUN_INITIAL_POSITION_Y 4000.0f
#define SUN_INITIAL_POSITION_Z -9000.0f

const float sun_size = 300.0f;

void sun_light_init() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat light_diffuse[] = {1.0f, 0.8f, 0.4f, 1.0f};
  GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  GLfloat sun_direction[] = {sun_x, sun_y, sun_z, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
}

void update_sun_position() {
  sun_x = SUN_INITIAL_POSITION_X - (get_global_player()->x * 1000 * PARALLAX_FACTOR);
  sun_y = SUN_INITIAL_POSITION_Y + (get_global_player()->y * 1000 * -PARALLAX_FACTOR);
  sun_z = SUN_INITIAL_POSITION_Z - (get_global_player()->z * 1000 * PARALLAX_FACTOR);
}

void draw_sun_square() {
  glPushMatrix();
  glDisable(GL_LIGHTING);

  glTranslatef(sun_x, sun_y, sun_z);
  glRotatef(45.0, 0.0f, 1.0f, 0.0f);

  glColor3f(1.0f, 0.9f, 0.6f);

  glBegin(GL_QUADS);
  glVertex3f(-sun_size / 2, -sun_size / 2, 0.0f);
  glVertex3f(sun_size / 2, -sun_size / 2, 0.0f);
  glVertex3f(sun_size / 2, sun_size / 2, 0.0f);
  glVertex3f(-sun_size / 2, sun_size / 2, 0.0f);
  glEnd();

  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void render_sun() {
  update_sun_position();
  draw_sun_square();
  GLfloat sun_position[] = {sun_x, sun_y, sun_z, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
}