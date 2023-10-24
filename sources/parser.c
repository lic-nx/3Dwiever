#include "../headers/parser.h"

// Открывает и читает файл .obj
// Возвращает код ошибки 0, если имя файла правильно, иначе - 1

int open_file(const char *path, obj_t *object) {
  int return_code = OK;
  char file[LENGTH] = {0};
  snprintf(file, sizeof(file), "%s", path);
  FILE *fp = fopen(file, "rt");
  if (fp) {
    return_code = parse_obj(fp, object);
    fclose(fp);
  } else {
    return_code = FILENAME_ERROR;
  }
  return return_code;
}

// Разбирает значения из файла .obj в структуру
// Возвращает ошибку код 0, если значения в файле правильные, иначе - 2

int parse_obj(FILE *fp, obj_t *object) {
  int return_code = OK;
  char line[LENGTH] = {0};
  while (fgets(line, LENGTH, fp) && return_code == OK) {
    if (*line == 'v' && *(line + 1) == ' ') {
      object->vertex_count++;
    } else if (*line == 'f' && *(line + 1) == ' ') {
      object->edge_count++;
    }
  }
  object->vertices = (double *)realloc(
      object->vertices, sizeof(double) * object->vertex_count * 3);
  object->edges =
      (int *)realloc(object->edges, sizeof(int) * object->edge_count * 6);
  if (object->vertices && object->edges) {
    fseek(fp, 0, SEEK_SET);
    int v_count = object->vertex_count;
    int e_count = object->edge_count;
    while (fgets(line, LENGTH, fp) && return_code == OK) {
      if (*line == 'v' && *(line + 1) == ' ') {
        return_code = parse_vertex(line, object, v_count);
        v_count--;
      } else if (*line == 'f' && *(line + 1) == ' ') {
        return_code = parse_edge(line, object, e_count);
        e_count--;
      }
    }
  }
  *line = '\0';
  return return_code;
}

// Разбирает значения вершины в структуру
// Возвращает ошибку код 0, если значения вершины правильные, иначе - 2

int parse_vertex(char *ptr, obj_t *object, int v_count) {
  int return_code = OK;
  ptr += 2;
  object->vertices[(object->vertex_count - v_count) * 3] = strtod(ptr, &ptr);
  if ((*ptr) != ' ') return_code = OBJ_VALUES_ERROR;
  object->vertices[(object->vertex_count - v_count) * 3 + 1] =
      strtod(ptr, &ptr);
  if ((*ptr) != ' ') return_code = OBJ_VALUES_ERROR;
  object->vertices[(object->vertex_count - v_count) * 3 + 2] =
      strtod(ptr, &ptr);
  return return_code;
}

// Разбирает значения ребер в структуру
// Возвращает ошибку код 0, если значения ребер правильные, иначе - 2

int parse_edge(char *ptr, obj_t *object, int e_count) {
  int return_code = OK;
  if (strchr(ptr, ' ') == NULL) return_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int first_index = (int)strtol(ptr, &ptr, 10) - 1;
  object->edges[(object->edge_count - e_count) * 6] = first_index;
  if (strchr(ptr, ' ') == NULL) return_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int second_index = (int)strtol(ptr, &ptr, 10) - 1;
  object->edges[(object->edge_count - e_count) * 6 + 1] = second_index;
  object->edges[(object->edge_count - e_count) * 6 + 2] = second_index;
  if (strchr(ptr, ' ') == NULL) return_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int third_index = (int)strtol(ptr, &ptr, 10) - 1;
  object->edges[(object->edge_count - e_count) * 6 + 3] = third_index;
  object->edges[(object->edge_count - e_count) * 6 + 4] = third_index;
  object->edges[(object->edge_count - e_count) * 6 + 5] = first_index;
  return return_code;
}

// Создает структуру obj_t

void init_obj(obj_t *object, int vertex_count, int edge_count) {
  object->vertices = (double *)calloc(vertex_count, sizeof(double));
  object->edges = (int *)calloc(edge_count, sizeof(int));
  object->vertex_count = 0;
  object->edge_count = 0;
}

// Удаляет структуру obj_t

void clean_obj(obj_t *object) {
  if (object) {
    if (object->vertices) {
      free(object->vertices);
    }
    if (object->edges) {
      free(object->edges);
    }
    object = NULL;
  }
}
