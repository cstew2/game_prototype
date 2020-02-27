#ifndef __ARENA_H__
#define __ARENA_H__

#include <SDL2/SDL.h>

#include "render.h"

typedef struct {
	int seed;
	SDL_Texture *background;
}arena;

arena *arena_init(sdl_state *state, char *filename);
int arena_term(arena *a);

#endif
