#ifndef __RENDER_H__
#define __RENDER_H__

typedef struct  {
	int window_height;
	int window_width;
	SDL_Window *window;
	SDL_Renderer *renderer;

	float aspect_ratio;
	float xscale;
	float yscale;
}sdl_state;

sdl_state *sdl_init();
int sdl_term(sdl_state *state);

#endif
