#include "graphics.h"

void calc_params(vertices_list_t *v_list, float *scale, float *x_cen, float *y_cen) {
  float x_min = v_list->vertices[0]->x_p, x_max = v_list->vertices[0]->x_p, x_dif = 0, scale_x = 0;
  float y_min = v_list->vertices[0]->y_p, y_max = v_list->vertices[0]->y_p, y_dif = 0, scale_y = 0;

  for(int i = 0; i < v_list->npoints; i++) {
    x_min = (v_list->vertices[i]->x_p < x_min) ? v_list->vertices[i]->x_p : x_min;
    x_max = (v_list->vertices[i]->x_p > x_max) ? v_list->vertices[i]->x_p : x_max;
    y_min = (v_list->vertices[i]->y_p < y_min) ? v_list->vertices[i]->y_p : y_min;
    y_max = (v_list->vertices[i]->y_p > y_max) ? v_list->vertices[i]->y_p : y_max;
  }

  *x_cen = (x_max + x_min) / 2;
  *y_cen = (y_max + y_min) / 2;

  x_dif = x_max - x_min;
  y_dif = y_max - y_min;

  scale_x = SCREEN_WIDTH / x_dif;
  scale_y = SCREEN_HEIGHT / y_dif;

  *scale = (scale_x < scale_y) ? scale_x : scale_y;
  *scale = 0.95 * *scale;
}

void render_object(SDL_Renderer* renderer, object_t *object, vertices_list_t *v_list) {
  float scale = 0, x_cen = 0, y_cen = 0;

  calc_params(v_list, &scale, &x_cen, &y_cen);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
  for(int f_index = 0; f_index < object->nfaces; f_index++) {                         // For each face
    for(int v_index = 0; v_index < object->faces[f_index].npoints - 1; v_index++) {  // Draw all but the last line
      SDL_RenderDrawLine(renderer, (object->faces[f_index].vertices[v_index]->x_p - x_cen) * scale + SCREEN_WIDTH/2,
                                   SCREEN_HEIGHT/2 - (object->faces[f_index].vertices[v_index]->y_p - y_cen) * scale,
                                   (object->faces[f_index].vertices[v_index+1]->x_p - x_cen) * scale + SCREEN_WIDTH/2,
                                   SCREEN_HEIGHT/2 - (object->faces[f_index].vertices[v_index+1]->y_p - y_cen) * scale);
    }
    SDL_RenderDrawLine(renderer, (object->faces[f_index].vertices[object->faces[f_index].npoints - 1]->x_p - x_cen) * scale + SCREEN_WIDTH/2,
                                  SCREEN_HEIGHT/2 - (object->faces[f_index].vertices[object->faces[f_index].npoints - 1]->y_p - y_cen) * scale,
                                  (object->faces[f_index].vertices[0]->x_p - x_cen) * scale + SCREEN_WIDTH/2,
                                  SCREEN_HEIGHT/2 - (object->faces[f_index].vertices[0]->y_p - y_cen) * scale);
  }

  SDL_RenderPresent(renderer);
}

