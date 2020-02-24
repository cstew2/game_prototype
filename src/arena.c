#include <stdlib.h>

#include <SDL2/SDL_image.h>

#include "arena.h"

arena *arena_init(sdl_state *state, char *filename)
{
	arena *a = malloc(sizeof(arena));
	SDL_Surface *temp = IMG_Load(filename);
	if(!temp) {
		printf("Can't load %s SDL2_Image Error: %s\n", filename, IMG_GetError());
		return NULL;
	}
	
	a->background = SDL_CreateTextureFromSurface(state->renderer, temp);
	if(!a->background) {
		return NULL;
	}
	return a;
}

int arena_term(arena *the_arena)
{

	return 0;
}
