#include "objread.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void read_obj(char *file_name, object_t *object, vertices_list_t *v_list) {
  
  /* Opening File */
  FILE* obj_file = (file_name == NULL) ? stdin : fopen(file_name, "r");
  if(obj_file == NULL) {
    fprintf(stderr, "Falha ao abrir o arquivo %s \n", file_name);
    exit(2);
  }

  /* Read Number of Points and Faces */

  // aux vars
  int n_points = 0, n_faces = 0;
  char *line = NULL, aux_str[4096];
  size_t len;

  while(getline(&line, &len, obj_file) != -1) {
    if(line[0] == 'v' && line[1] == ' ') n_points++;
    if(line[0] == 'f') n_faces++;
  }

  printf("Points: %i Faces: %i \n", n_points, n_faces);

  /* Allocating Memory */
  v_list->vertices = malloc(n_points * sizeof(vertex_t *));
  object->faces = malloc(n_faces * sizeof(face_t));

  if(v_list->vertices == NULL || object->faces == NULL) {
    fprintf(stderr, "Falha ao alocar memoria para leitura do objeto!\n");
    exit(2);
  }

  for(int i = 0; i < n_points; ++i) {
    v_list->vertices[i] = malloc(sizeof(vertex_t));
    if(v_list->vertices[i] == NULL) {
      fprintf(stderr, "Falha ao alocar memoria para ponto!\n");
      exit(2);
    }
  }

  v_list->npoints = n_points;
  object->nfaces = n_faces;

  /* Read an allocate points/faces */

  int v_index = 0, f_index = 0;
  char spc_del[2] = " ";
  char *token = NULL;

  rewind(obj_file);
  while(getline(&line, &len, obj_file) != -1) {

    // Reading a vertex
    if(line[0] == 'v' && line[1] == ' ') {
      token = strtok(line, spc_del); // Token receives line identifier

      token = strtok(NULL, spc_del); // Token receives x
      sscanf(token,"%f", &v_list->vertices[v_index]->x);

      token = strtok(NULL, spc_del); // Token receives y
      sscanf(token,"%f", &v_list->vertices[v_index]->y);

      token = strtok(NULL, spc_del); // Token receives z
      sscanf(token,"%f", &v_list->vertices[v_index]->z);

      v_index++;
    }

    // Reading a face
    if(line[0] == 'f') {
      strcpy(aux_str, line);

      // Reading number of points in face
      int points_face = -1, point_pos = 0, iterator = 0;
      token = strtok(aux_str, spc_del); // Token receives line identifier
      while(token != NULL) {
        token = strtok(NULL, spc_del); // Jump to next space
        points_face++;
      }

      object->faces[f_index].vertices = malloc(points_face * sizeof(vertex_t *));
      object->faces[f_index].npoints = points_face;
      if(object->faces[f_index].vertices == NULL) {
        fprintf(stderr, "Falha ao alocar memoria para face!\n");
        exit(2);
      }

      token = strtok(line, spc_del); // Token receives line identifier
      token = strtok(NULL, spc_del); // Jump to next space
      while(token != NULL) {
        sscanf(token,"%i",&point_pos);
        object->faces[f_index].vertices[iterator++] = v_list->vertices[point_pos-1];
        token = strtok(NULL, spc_del); // Jump to next space
      }

      f_index++;
    }

  }

  // closing file
  fclose(obj_file);
}