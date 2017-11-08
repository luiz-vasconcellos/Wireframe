#include "perspect.h"

void calc_perspect_vertex(vertex_t *p, observer_t c) {
  p->x_p = c.x + c.z * ((p->x - c.x) / (p->z + c.z));
  p->y_p = c.y + c.z * ((p->y - c.y) / (p->z + c.z));
}


void calc_perspect_list(vertices_list_t *v_list, observer_t observer) {
  for(int i = 0; i < v_list->npoints; ++i)
    calc_perspect_vertex(v_list->vertices[i], observer);
}