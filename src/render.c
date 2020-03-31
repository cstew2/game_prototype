#include <stdlib.h>

#include <SDL2/SDL_ttf.h>

#include "render.h"

sdl_state *sdl_init()
{
	if(SDL_Init(SDL_INIT_AUDIO |
		    SDL_INIT_TIMER |
		    SDL_INIT_VIDEO |
		    SDL_INIT_EVENTS |
		    SDL_INIT_GAMECONTROLLER)) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return NULL;
	}
	
	sdl_state *state = calloc(1, sizeof(sdl_state));
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
		printf("%s\n", SDL_GetError());
		return NULL;
	}
        
	state->renderer = SDL_CreateRenderer(state->window,
					     -1,
					     SDL_RENDERER_ACCELERATED |
					     SDL_RENDERER_PRESENTVSYNC);
	if(!state->renderer) {
		printf("%s", SDL_GetError());
		return NULL;
	}

	if(TTF_Init()) {
		printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
		return NULL;
	}
	
	return state;
}
int sdl_term(sdl_state *state)
{
	TTF_Quit();
	SDL_DestroyRenderer(state->renderer);
	SDL_DestroyWindow(state->window);
	free(state);
	SDL_Quit();
	return 0;
}

