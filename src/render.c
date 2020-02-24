#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "render.h"

sdl_state *sdl_init()
{
	sdl_state *state = malloc(sizeof(sdl_state));
	state->window_width = 500;
	state->window_height = 500;
	
	state->window = SDL_CreateWindow("Graph Battle",
					 SDL_WINDOWPOS_UNDEFINED,
					 SDL_WINDOWPOS_UNDEFINED,
					 state->window_width,
					 state->window_height,
					 SDL_WINDOW_SHOWN);
	if(!state->window) {
		return NULL;
	}
        
	state->renderer = SDL_CreateRenderer(state->window,
					     -1,
					     SDL_RENDERER_ACCELERATED);
	if(!state->renderer) {
		return NULL;
	}

	int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(IMG_Init(img_flags) & img_flags) {
		printf("Error initializing SDL image library\n");
		return NULL;
	}

	return state;
}
int sdl_term(sdl_state *state)
{
	IMG_Quit();
	SDL_DestroyRenderer(state->renderer);
	SDL_DestroyWindow(state->window);
	free(state);
	return 0;
}

