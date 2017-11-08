#ifndef DATATYPES_H
#define DATATYPES_H

typedef struct vertex_t {
  float x;
  float y;
  float z;

  float x_p;
  float y_p;
} vertex_t;

/* A List of pointers to points */
typedef struct vertices_list_t {
  vertex_t **vertices;
  int npoints;
} vertices_list_t;

/* A face is just a list of points */
typedef vertices_list_t face_t;

typedef struct object_t {
  face_t *faces;
  int nfaces;
} object_t;

typedef struct observer_t {
  float x;
  float y;
  float z;
} observer_t;

#endif