#include "datatypes.h"
#include "objread.h"
#include "perspect.c"

#include <stdio.h>


int main(int argc, char* argv[]) {

  object_t object;
  vertices_list_t v_list;

  read_obj(argv[1], &object, &v_list);

  for(int i = 0; i < v_list.npoints; ++i)
    printf("(%.2f, %.2f, %.2f)\n", v_list.vertices[i]->x,v_list.vertices[i]->y,v_list.vertices[i]->z);
}