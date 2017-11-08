#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "datatypes.h"
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void render_object(SDL_Renderer *renderer, object_t *object, vertices_list_t *v_list);

#endif