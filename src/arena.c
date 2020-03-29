#include <stdlib.h>

#include "arena.h"
#include "shapes.h"

arena *arena_init(sdl_state *state, int size_x, int size_y)
{
	arena *a = calloc(1, sizeof(arena));

	uint32_t *bitmap = calloc(state->window_width * state->window_height, sizeof(uint32_t));
	uint32_t blue = 0x1020FFFF;

	int x_i = state->window_width/size_x;
	int y_i = state->window_height/size_y;
	int x_start = (state->window_width % size_x)/2;
	int y_start = (state->window_height % size_y)/2;
	
	for(int x=x_start; x < state->window_width; x+=x_i) {
		draw_line(bitmap, blue, state->window_width, x, x, 0, state->window_height);
	}

	for(int y=y_start; y < state->window_height; y+=y_i) {
	        draw_line(bitmap, blue, state->window_width, 0, state->window_width, y, y);
	}	

	SDL_Surface *temp = SDL_CreateRGBSurfaceFrom((void *)bitmap,
						     state->window_width,
						     state->window_height,
						     32,
						     4*state->window_width,
						     0xFF000000,
						     0x00FF0000,
						     0x0000FF00,
						     0x000000FF);
	
	if(!temp) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}
	a->background = SDL_CreateTextureFromSurface(state->renderer, temp);
	free(bitmap);
	SDL_FreeSurface(temp);
	if(!a->background) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}
	
	return a;
}

int arena_term(arena *a)
{
	SDL_DestroyTexture(a->background);
	free(a);
	return 0;
}
