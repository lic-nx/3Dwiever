#include "headers/glview.h"

glView::glView(QWidget* parent) : QOpenGLWidget(parent) {
  xRot = 4;
  yRot = 0;
  zRot = 0;
  xPos = 0;
  yPos = 0;
  zPos = -4;
  xR = 0;
  yR = 0;
  zR = 0;
  x = 0;
  y = 0;
  z = 0;
  nSca = 1;
  project = false;
}

void glView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void glView::DrawObject(obj_t* object) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, object->vertices);
  if (vertex_shape > 0) {
    if (vertex_shape == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(vertex_size);
    glColor3d(vertex_r / 255.0, vertex_g / 255.0, vertex_b / 255.0);
    glDrawArrays(GL_POINTS, 0, object->vertex_count);
  }
  if (edge_type == 0) {
    glDisable(GL_LINE_STIPPLE);
  } else {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1111);
  }

  glLineWidth(edge_width);
  glColor3d(edge_r / 255.0, edge_g / 255.0, edge_b / 255.0);
  glDrawElements(GL_LINES, object->edge_count * 6, GL_UNSIGNED_INT,
                 object->edges);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::paintGL() {
  glClearColor(bg_color_r / 255.0, bg_color_g / 255.0, bg_color_b / 255.0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (proj_type) {
    nSca = 4;
    glFrustum(-1, 1, -1, 1, 1, qPow(3000, 2));
  } else {
    if (nSca == 4) {
      nSca = 1;
    }
    ratio = (GLfloat)600 / (GLfloat)600;
    glOrtho(-2.0 / ratio, 2.0 / ratio, -2.0, 2.0, -50.0, 50.0);
  }
  glScalef(nSca, nSca, nSca);
  glTranslatef(xPos, 0, 0);
  glTranslatef(0, yPos, 0);
  glTranslatef(0, 0, zPos);
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  glRotatef(zRot, 0.0f, 0.0f, 1.0f);
  if (grid_status) {
    DrawAxis();
    DrawGrid(100.0, 100.0, 1.0);
  }
  if (project) DrawObject(obj);
}

void glView::DrawAxis() {
  glLineWidth(3.0f);
  glColor4f(1.0f, 0.0f, 0.0f, 0.3);
  glBegin(GL_LINES);
  glVertex3f(-1.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glEnd();
  glColor4f(0.0f, 1.0f, 0.0f, 0.3);
  glBegin(GL_LINES);
  glVertex3f(0.0f, -1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glColor4f(0.0f, 0.0f, 1.0f, 0.3);
  glVertex3f(0.0f, 0.0f, -1.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glEnd();
}

void glView::DrawGrid(float cx, float cy, float step) {
  float _cx = cx / 2;
  float _cy = cy / 2;
  glLineStipple(1, 0xAAAA);
  glStencilFunc(GL_NOTEQUAL, 1, 255);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_TRIANGLE_FAN);
  glColor4d(1, 1, 1, 0.3);
  for (int x = -_cx; x <= _cx; x += step) {
    glBegin(GL_LINE_STRIP);
    glVertex3f(x, 0, _cy);
    glVertex3f(x, 0, -_cy);
    glEnd();
  }
  for (int y = -_cy; y <= _cy; y += step) {
    glBegin(GL_LINE_STRIP);
    glVertex3f(_cx, 0, y);
    glVertex3f(-_cx, 0, y);
    glEnd();
  }
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_STENCIL_TEST);
}

void glView::mouseMoveEvent(QMouseEvent* mme) {
  double translateSensative = 100;
  static int currentX = 0;
  static int currentY = 0;
  if (!currentX && !currentY) {
    currentX = mme->pos().x();
    currentY = mme->pos().y();
  }
  if (abs(mme->pos().x() - currentX) < translateSensative &&
      abs(mme->pos().y() - currentY) < translateSensative) {
    if (mme->buttons() & Qt::LeftButton) {
      xPos += 0.01 / nSca * (mme->pos().x() - mPos.x());
      yPos += -0.01 / nSca * (mme->pos().y() - mPos.y());
      x = (xPos) / -M_PI;
      y = (yPos) / -M_PI;
    } else {
      xRot += 1 / M_PI * (mme->pos().y() - mPos.y());
      yRot += 1 / M_PI * (mme->pos().x() - mPos.x());
      zRot += 0.01 / M_PI * (sin(xRot));
      xR = xRot / -M_PI;
      yR = yRot / -M_PI;
      zR = zRot;
    }
  }

  mPos = mme->pos();
  currentX = mme->pos().x();
  currentY = mme->pos().y();
  update();
}

void glView::mousePressEvent(QMouseEvent* mpe) { mPos = mpe->pos(); }

void glView::wheelEvent(QWheelEvent* we) {
  if (proj_type) {
    int temp = we->angleDelta().y();
    if (temp > 0)
      zPos += 0.1;
    else if (temp < 0)
      zPos -= 0.1;
  } else {
    int temp = we->angleDelta().y();
    if (temp > 0)
      nSca += 0.1;
    else if (temp < 0 && nSca > 0.2)
      nSca -= 0.1;
  }
  update();
}
