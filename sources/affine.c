#include "../headers/parser.h"

// Смещение вершины по оси X

void move_x(obj_t* object, float value) {
  for (int i = 0; i < object->vertex_count; i++) {
    object->vertices[3 * i] += value;
  }
}

// Смещение вершины по оси Y

void move_y(obj_t* object, float value) {
  for (int i = 0; i < object->vertex_count; i++) {
    object->vertices[3 * i + 1] += value;
  }
}

// Смещение вершины по оси Z

void move_z(obj_t* object, float value) {
  for (int i = 0; i < object->vertex_count; i++) {
    object->vertices[3 * i + 2] += value;
  }
}

// Вращает вершину по оси x
// Х = Х
// Y = Y*cos(a) + Z*sin(a)
// Z =-Y*sin(a) + Z*cos(a)

void rotate_x(obj_t* object, float angle) {
  for (int i = 0; i < object->vertex_count; i++) {
    double y = object->vertices[3 * i + 1];
    double z = object->vertices[3 * i + 2];
    object->vertices[3 * i + 1] = y * cos(angle) - z * sin(angle);
    object->vertices[3 * i + 2] = y * sin(angle) + z * cos(angle);
  }
}

// Вращает вершину по оси Y
// X = X*cos(a) - Z*sin(a)
// Y = Y
// Z = X*sin(a) + Z*cos(a)

void rotate_y(obj_t* object, float angle) {
  for (int i = 0; i < object->vertex_count; i++) {
    double x = object->vertices[3 * i];
    double z = object->vertices[3 * i + 2];
    object->vertices[3 * i] = x * cos(angle) + z * sin(angle);
    object->vertices[3 * i + 2] = -x * sin(angle) + z * cos(angle);
  }
}

// Вращает вершину по оси Z
// X = X*cos(a) + Y*sin(a)
// Y =-X*sin(a) + Y*cos(a)
// Z = Z

void rotate_z(obj_t* object, float angle) {
  for (int i = 0; i < object->vertex_count; i++) {
    double x = object->vertices[3 * i];
    double y = object->vertices[3 * i + 1];
    object->vertices[3 * i] = x * cos(angle) - y * sin(angle);
    object->vertices[3 * i + 1] = x * sin(angle) + y * cos(angle);
  }
}

// Масштабирует вершину по соотношению коэффициентов

void scale(obj_t* object, float ratio) {
  if (ratio > 0) {
    for (int i = 0; i < (object->vertex_count) * 3; i++) {
      object->vertices[i] *= ratio;
    }
  }
}
