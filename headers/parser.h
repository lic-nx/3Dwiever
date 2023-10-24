#ifndef PARSER_H
#define PARSER_H

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1e-6
#define LENGTH 255

typedef struct obj_struct {
  double *vertices;
  int *edges;
  int vertex_count;
  int edge_count;
} obj_t;

enum obj_returns {
  OK,
  FILENAME_ERROR,
  OBJ_VALUES_ERROR,
};

int open_file(const char *path, obj_t *object);
int parse_obj(FILE *fp, obj_t *object);
int parse_vertex(char *ptr, obj_t *object, int v_count);
int parse_edge(char *ptr, obj_t *object, int e_count);
void init_obj(obj_t *object, int vertex_count, int edge_count);
void clean_obj(obj_t *object);

void move_x(obj_t *object, float value);
void move_y(obj_t *object, float value);
void move_z(obj_t *object, float value);
void rotate_x(obj_t *object, float angle);
void rotate_y(obj_t *object, float angle);
void rotate_z(obj_t *object, float angle);
void scale(obj_t *object, float ratio);

#endif  // PARSER_H
