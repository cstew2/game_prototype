#include <stdlib.h>

#include <SDL2/SDL.h>

#include "render.h"

sdl_state *sdl_init()
{
	sdl_state *state = malloc(sizeof(sdl_state));
	state->window_width = 500;
	state->window_height = 500;

	state->aspect_ratio = 1.0;
	state->xscale = 1.0;
	state->yscale = 1.0;
	
	state->window = SDL_CreateWindow("Graph Battle",
					 SDL_WINDOWPOS_UNDEFINED,
					 SDL_WINDOWPOS_UNDEFINED,
					 state->window_width,
					 state->window_height,
					 SDL_WINDOW_SHOWN);
	if(!state->window) {
		printf("%s", SDL_GetError());
		return NULL;
	}
        
	state->renderer = SDL_CreateRenderer(state->window,
					     -1,
					     SDL_RENDERER_ACCELERATED);
	if(!state->renderer) {
		printf("%s", SDL_GetError());
		return NULL;
	}
	
	return state;
}
int sdl_term(sdl_state *state)
{
	SDL_DestroyRenderer(state->renderer);
	SDL_DestroyWindow(state->window);
	free(state);
	return 0;
}

