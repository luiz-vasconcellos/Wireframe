#include "datatypes.h"
#include "objread.h"
#include "perspect.h"
#include "graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main (int argc, char* argv[]) {

  /* Our variables */
  object_t object;
  vertices_list_t v_list;
  observer_t observer = { 100.0f, 100.0f, 100.0f };
  char *file_name = (argc == 2) ? argv[1] : NULL;

  /* Read object from file or stdin */
  read_obj(file_name, &object, &v_list);

  /* SDL Initialization */
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Falha ao inicializar SDL!\n");
    exit(1);
  }

  SDL_Window *window     = NULL;
  SDL_Renderer *renderer = NULL;

  if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0) {
    fprintf(stderr, "Falha ao criar a janela principal!\n");
    exit(1);
  }

  /* Main loop */
  int done = 0;
  while(!done) {

    /* Input handling */
    SDL_Event ev;
    while(SDL_PollEvent(&ev)) {
      switch(ev.type) {
      case SDL_QUIT:
        done = 1;
        break;

      case SDL_KEYDOWN:
        switch(ev.key.keysym.sym) {
          case SDLK_UP:
            observer.y -= 10;
            break;
          case SDLK_DOWN:
            observer.y += 10;
            break;
          case SDLK_LEFT:
            observer.x += 10;
            break;
          case SDLK_RIGHT:
            observer.x -= 10;
          break;
          case SDLK_q:
            done = 1;
            break;
          default:
            break;
        }

        break;

      default:
        break;
      }
    }

    /* Update state of our program */
    calc_perspect_list(&v_list, observer);

    /* Render to the window */
    render_object(renderer, &object, &v_list);
  }


  /* Wrapping up before closing */
  if(renderer != NULL)
    SDL_DestroyRenderer(renderer);
  if(window != NULL)
    SDL_DestroyWindow(window);

  // Remember to free our objects !
}