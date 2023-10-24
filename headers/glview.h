#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QWheelEvent>

extern "C" {
#include "headers/parser.h"
}

class glView : public QOpenGLWidget {
  Q_OBJECT

 private:
  void initializeGL() override;
  void paintGL() override;
  void DrawObject(obj_t *obj);
  void DrawGrid(float cx, float cy, float step);
  void DrawAxis();
  void mouseMoveEvent(QMouseEvent *) override;
  void mousePressEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *we) override;
  QPoint mPos;
  GLfloat ratio;

 public:
  glView(QWidget *parent = nullptr);
  obj_t *obj;
  double xRot, yRot, zRot;
  double nSca;
  double xPos, yPos, zPos;
  double xR, yR, zR;
  double x, y, z;
  double bg_color_r, bg_color_g, bg_color_b;
  double vertex_r, vertex_g, vertex_b;
  double edge_r, edge_g, edge_b;
  int vertex_size, vertex_shape, edge_width, edge_type, proj_type, grid_status;
  bool project;
};

#endif  // GLVIEW_H
