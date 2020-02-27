#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "render.h"

typedef struct {
	SDL_Texture *sprite;
	int width;
	int height;
	float x;
	float y;
	float vel;

	bool up;
	bool down;
	bool left;
	bool right;
	
}player;

player *player_init(sdl_state *state, char *filename, int x, int y, float delta);
int player_term(player *p);

#endif
