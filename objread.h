#ifndef OBJREAD_H
#define OBJREAD_H

#include "datatypes.h"

/*
  Read the object from a file. (Or stdin in case of NULL file_name)
  Allocate the points in the v_list, but organizes references to
  them in faces (object).
*/
void read_obj(char *file_name, object_t *object, vertices_list_t *v_list);

#endif